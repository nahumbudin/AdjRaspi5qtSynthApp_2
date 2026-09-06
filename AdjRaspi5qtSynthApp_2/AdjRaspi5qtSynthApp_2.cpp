/**
 * @file		AdjRaspi5qtSynthApp_2.cpp
 *	@author		Nahum Budin
 *	@Date		13-Dec-2025
 *	@version	2.0
 *					1. Execute system command with error checking
 *					2. Handle log file opening errors and ensure proper cleanup on application exit.
 *					3. Add results check for all initialization functions and log errors if any of them fail.
 *					4. Handling for potential double cleanup in exit handler to prevent issues if both 
 *					   atexit and Qt's aboutToQuit are triggered.
 *
 *	History:\n
 *		- AdjRaspi5qtSynthApp_2
 */

#include "MainWindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <QVariant>
#include <QDebug>
#include <QFont>
#include <QFontDatabase>
#include <QFileInfo>

#include "HttpBridgeQt.h"
#include "Dialog_HTTPserver.h"

#include "Log.h"

#include <qprocess.h>

#include <unistd.h> // for nice()

static bool cleanup_done = false;

/**
 *   @brief  Execute system command with error checking
 *   @param  cmd - command to execute
 *   @return true if successful, false otherwise
 */
static bool execute_system_command(const char *cmd)
{
	int result = system(cmd);
	if (result != 0)
	{
		fprintf(stderr, "Warning: Command failed: %s (exit code: %d)\n", cmd, result);
		return false;
	}
	return true;
}

/**
*   @brief  Runs on application exit.
*   @param  none
*   @return void
*/
void exit_handler(void)
{
	if (cleanup_done) return; // Prevent double cleanup
	
	cleanup_done = true;

	printf("Program terminated! Running cleanup...\n");

	mod_synth_on_exit();

	// Close log file if open
	FILE *pFile = Output2FILE::Stream();
	if (pFile && pFile != stderr && pFile != stdout)
	{
		fflush(pFile);
		fclose(pFile);
		Output2FILE::Stream() = stderr; // Reset to stderr
	}

	execute_system_command("xset s blank");
	execute_system_command("xset s on");
	execute_system_command("xset -dpms");

	execute_system_command("pactl unload-module module-jack-sink");
	execute_system_command("pactl unload-module module-jack-source");

	execute_system_command("cpu.gov -g ondemand");
}

int main(int argc, char *argv[])
{
	// Set clock control and priority	
	/*
	* https://github.com/DavidM42/rpi-cpu.gov
	*
	* install: wget https://raw.githubusercontent.com/DavidM42/rpi-cpu.gov/master/install.sh && sudo chmod +x ./install.sh && sudo ./install.sh --nochown && sudo rm install.sh
	*
	**/
	system("cpu.gov -g performance");
	// Disable screen saver
	system("xset s noblank");
	system("xset s off");
	system("xset -dpms");

//	To allow nice() to work without sudo, run this command once 
//  #Grant capability to your executable
// sudo setcap cap_sys_nice = eip / path / to / AdjRaspi5qtSynthApp_2

	int nice_result = nice(0); // was 20 is default, -20 is highest priority. Requires appropriate permissions.
	if (nice_result == -1)
	{
		fprintf(stderr, "Warning: Failed to set process priority. Run with sudo for better real-time performance.\n");
	}

	setbuf(stderr, NULL);
	atexit(exit_handler);
	
	// Debuger
	FILELog::ReportingLevel() = FILELog::FromString("DEBUG4");
	FILE *pFile = fopen("AdjHeartRaspi5FlSynth2_0.log", "w"); // "a" for append, "w" for overwrite
	if (pFile != NULL)
	{
		Output2FILE::Stream() = pFile;
	}
	else
	{
		fprintf(stderr, "Warning: Failed to open log file 'AdjHeartRaspi5FlSynth2_0.log'. Logging to file disabled.\n");
	}
	//	FILE_LOG(logINFO) << "...";

	int result;

	result = mod_synth_init();
	if (result != 0)
	{
		fprintf(stderr, "Error: mod_synth_init() failed with code %d\n", result);
		// Cleanup before exit
		if (pFile != NULL)
		{
			fflush(pFile);
			fclose(pFile);
		}
		return 1; // Critical - cannot continue without synth
	}

	result = mod_synth_start_audio();
	if (result != 0)
	{
		fprintf(stderr, "Error: mod_synth_start_audio() failed with code %d\n", result);
		// Cleanup before exit
		if (pFile != NULL)
		{
			fflush(pFile);
			fclose(pFile);
		}
		return 1; // Critical - no audio means no synth
	}

	result = mod_synth_init_fluid_synth();
	if (result != 0)
	{
		fprintf(stderr, "Error: mod_synth_init_fluid_synth() failed with code %d\n", result);
		// Cleanup before exit
		if (pFile != NULL)
		{
			fflush(pFile);
			fclose(pFile);
		}
		return 1; // Critical - cannot continue without FluidSynth
	}

	result = mod_synth_init_bt_services();
	if (result != 0)
	{
		fprintf(stderr, "Warning: mod_synth_init_bt_services() failed with code %d - Bluetooth disabled\n", result);
		// Non-critical - continue without BT
	}

	result = mod_synth_init_ext_midi_services(_MIDI_EXT_INTERFACE_SERIAL_PORT_NUM);
	if (result != 0)
	{
		fprintf(stderr, "Warning: mod_synth_init_ext_midi_services() failed with code %d - External MIDI disabled\n", result);
		// Non-critical - continue without external MIDI
	}

	result = mod_synth_init_midi_services();
	if (result != 0)
	{
		fprintf(stderr, "Error: mod_synth_init_midi_services() failed with code %d\n", result);
		// Cleanup before exit
		if (pFile != NULL)
		{
			fflush(pFile);
			fclose(pFile);
		}
		return 1; // Critical - MIDI services required
	}
	
	
	QApplication app(argc, argv);

	// Ensure default font is available
	// Try to explicitly load a known system font FIRST
	QString fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf";
	int fontId = -1;

	// Check if font file exists before trying to load it
	QFileInfo fontFile(fontPath);
	if (fontFile.exists())
	{
		fontId = QFontDatabase::addApplicationFont(fontPath);
		if (fontId == -1)
		{
			fprintf(stderr, "Warning: Failed to load font from %s\n", fontPath.toStdString().c_str());
		}
		else
		{
			printf("Successfully loaded DejaVu Sans font (ID: %d)\n", fontId);
		}
	}
	else
	{
		fprintf(stderr, "Warning: Font file not found: %s\n", fontPath.toStdString().c_str());
	}

	// Now set a fallback font
	QFont font;
	font.setFamily("DejaVu Sans");
	font.setPointSize(10);
	font.setStyleHint(QFont::SansSerif, QFont::PreferAntialias); // Provide a fallback hint
	QApplication::setFont(font);

	// Verify the font was actually set
	QFont actualFont = QApplication::font();
	printf("Active font family: %s\n", actualFont.family().toStdString().c_str());

	// List available fonts for debugging
	QStringList fontFamilies = QFontDatabase().families();
	printf("Available font families: %d\n", fontFamilies.size());
	if (fontFamilies.isEmpty())
	{
		fprintf(stderr, "CRITICAL: No fonts available in Qt font database! Check fontconfig installation.\n");
		// Consider exiting or using software rendering
	}

	// Connect to Qt's aboutToQuit signal**
	QObject::connect(&app, &QApplication::aboutToQuit, [pFile]() {
		if (cleanup_done)
			return; // Prevent double cleanup
		cleanup_done = true;

		printf("Qt application is quitting - running cleanup...\n");
		mod_synth_on_exit();

		execute_system_command("xset s blank");
		execute_system_command("xset s on");
		execute_system_command("xset -dpms");
		execute_system_command("pactl unload-module module-jack-sink");
		execute_system_command("pactl unload-module module-jack-source");
		execute_system_command("cpu.gov -g ondemand");

		if (pFile != NULL)
		{
			fflush(pFile);
			fclose(pFile);
		}
	});
	
	// Force Fusion style for consistency across platforms
	QStringList availableStyles = QStyleFactory::keys();
	if (availableStyles.contains("Fusion", Qt::CaseInsensitive))
	{
		app.setStyle(QStyleFactory::create("Fusion"));
		printf("Using Fusion style\n");
	}
	else
	{
		fprintf(stderr, "Warning: Fusion style not available. Available styles: %s\n",
				availableStyles.join(", ").toStdString().c_str());
	}
	
	MainWindow w;
	w.show();
    
	return app.exec();
}