/**
 * @file		WidgetsSelection.cpp
 *	@author		Nahum Budin
 *	@date		19-June-2026
 *	@version	1.0
 *
 *	@brief		Handle the widgets selection for ML training in the main window. 
 *				When enabled, clicking on a widget will open a dialog to select the parameter for ML training.
 *
 *	History:
 *
 */

#include <QDebug>
#include <QComboBox>
#include <QTimer>

#include "MainWindow.h"
#include "Dialog_SelectMLtrainingParam.h"

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
	QString MAX_str = "";
	QString MIN_str;

	QStringList max_str_list;
	QStringList min_str_list;

	if (event->type() == QEvent::MouseButtonPress)
	{
		if (widgets_selection_active)
		{
			// Check if a dialog is already open
			if (MainWindow::active_ml_param_dialog != nullptr)
			{
				// Bring existing dialog to front
				MainWindow::active_ml_param_dialog->raise();
				MainWindow::active_ml_param_dialog->activateWindow();
				return true; // Event consumed
			}
			
			// Mouse click detected on a registered widget
			QWidget *widget = qobject_cast<QWidget *>(watched);
			if (widget)
			{
				qDebug() << "Widget clicked:" << widget;
				qDebug() << "Map size:" << widgets_map_ml_training_info.size();

				auto it = widgets_map_ml_training_info.find(widget);
				if (it != widgets_map_ml_training_info.end())
				{
					qDebug() << "✓ Found in map!";
					int module = it->second[0];
					QString module_name = QString(modules_names_map[module].c_str());
					
					int submodule = it->second[1];
					QString submodule_name = QString(submodules_names_map[submodule].c_str());

					int param = it->second[2];
					QString param_name = QString(params_names_map[param].c_str());

					int MAX = it->second[3];
					int MIN = it->second[4];
					int max = it->second[5];
					int min = it->second[6];
					int mode = it->second[7];
					int type = it->second[8];

					MainWindow::param_info[0] = module;
					MainWindow::param_info[1] = submodule;
					MainWindow::param_info[2] = param;
					MainWindow::param_info[3] = MAX;
					MainWindow::param_info[4] = MIN;
					MainWindow::param_info[5] = max;
					MainWindow::param_info[6] = min;
					MainWindow::param_info[7] = mode;

					if (type == _WIDGET_TYPE_COMBOBOX)
					{
						// Combbox requires special handling to get the actual value range
						// and how to sedlect the min and max values for ML training.

						QComboBox *comboBox = qobject_cast<QComboBox *>(widget);
						if (comboBox)
						{
							// Close popup with a delay to ensure it closes after opening
							QTimer::singleShot(10, comboBox, [comboBox]() {
								comboBox->hidePopup();
							});
						}
						
						switch (submodule)
						{
						case _OSC_1_EVENT:
						case _OSC_2_EVENT:

							switch (param)
							{
							case _OSC_PARAM_WAVEFORM:
								MAX_str = QString("Sample and Hold");
								MIN_str = QString("Sine");
								max_str_list << "Sine" << "Square" << "Pulse" << "Triangle" << "Sample and Hold";
								min_str_list << "Sine" << "Square" << "Pulse" << "Triangle" << "Sample and Hold";

								break;

							case _OSC_DETUNE_OCTAVE:
								for (int i = _OSC_DETUNE_MIN_OCTAVE; i <= _OSC_DETUNE_MAX_OCTAVE; i++)
								{
									max_str_list << QString::number(i);
									min_str_list << QString::number(i);
								}
								break;

							case _OSC_DETUNE_SEMITONES:
								for (int i = _OSC_DETUNE_MIN_SEMITONES; i <= _OSC_DETUNE_MAX_SEMITONES; i++)
								{
									max_str_list << QString::number(i);
									min_str_list << QString::number(i);
								}
								break;

							case _OSC_DETUNE_CENTS:
								for (int i = 4 * _OSC_DETUNE_MIN_CENTS; i <= 4 * _OSC_DETUNE_MAX_CENTS; i++)
								{
									// 0.25 steps
									max_str_list << QString::number(i / 4.f);
									min_str_list << QString::number(i / 4.f);
								}
								break;								

							case _OSC_FREQ_MOD_LFO:
							case _OSC_AMP_MOD_LFO:
							case _OSC_PWM_MOD_LFO:
								max_str_list << "None" 
											 << "LFO 1" << "LFO 1 0.5sec" << "LFO 1 1sec" << "LFO 1 1.5sec" << "LFO 1 2sec"
											 << "LFO 2" << "LFO 2 0.5sec" << "LFO 2 1sec" << "LFO 2 1.5sec" << "LFO 2 2sec"
											 << "LFO 3" << "LFO 3 0.5sec" << "LFO 3 1sec" << "LFO 3 1.5sec" << "LFO 3 2sec"
											 << "LFO 4" << "LFO 4 0.5sec" << "LFO 4 1sec" << "LFO 4 1.5sec" << "LFO 4 2sec"
											 << "LFO 5" << "LFO 5 0.5sec" << "LFO 5 1sec" << "LFO 5 1.5sec" << "LFO 5 2sec"
											 << "LFO 6" << "LFO 6 0.5sec" << "LFO 6 1sec" << "LFO 6 1.5sec" << "LFO 6 2sec";

								min_str_list << "None" << "LFO 1" << "LFO 1 0.5sec" << "LFO 1 1sec" << "LFO 1 2sec"
											 << "LFO 2" << "LFO 2 0.5sec" << "LFO 2 1sec" << "LFO 2 1.5sec" << "LFO 2 2sec"
											 << "LFO 3" << "LFO 3 0.5sec" << "LFO 3 1sec" << "LFO 3 1.5sec" << "LFO 3 2sec"
											 << "LFO 4" << "LFO 4 0.5sec" << "LFO 4 1sec" << "LFO 4 1.5sec" << "LFO 4 2sec"
											 << "LFO 5" << "LFO 5 0.5sec" << "LFO 5 1sec" << "LFO 5 1.5sec" << "LFO 5 2sec"
											 << "LFO 6" << "LFO 6 0.5sec" << "LFO 6 1sec" << "LFO 6 1.5sec" << "LFO 6 2sec";
								
								break;

							case _OSC_FREQ_MOD_ENV:
							case _OSC_AMP_MOD_ENV:
							case _OSC_PWM_MOD_ENV:
								max_str_list << "None" << "ADSR 1" << "ADSR 2" << "ADSR 3" << "ADSR 4" << "ADSR 5" << "ADSR 6";
								min_str_list << "None" << "ADSR 1" << "ADSR 2" << "ADSR 3" << "ADSR 4" << "ADSR 5" << "ADSR 6";
								break;
								
							case _OSC_UNISON_MODE:
								max_str_list << "12345678" << "Hammond" << "Octaves" << "C Chord" << "Cm Chord" << "C7 Chord" << "Cm7 Chord";
								min_str_list << "12345678" << "Hammond" << "Octaves" << "C Chord" << "Cm Chord" << "C7 Chord" << "Cm7 Chord";
								break;
								
							case _OSC_HAMMOND_PERCUSION_MODE:
								max_str_list << "Off" << "2nd Soft Slow" << "2nd Soft Fast" << "2nd Norm Slow" << "2nd Norm Fast" 
											 << "3rd Soft Slow" << "3rd Soft Fast" << "3rd Norm Slow" << "3rd Norm Fast";
								min_str_list << "Off" << "2nd Soft Slow" << "2nd Soft Fast" << "2nd Norm Slow" << "2nd Norm Fast"
											 << "3rd Soft Slow" << "3rd Soft Fast" << "3rd Norm Slow" << "3rd Norm Fast";
								break;
							}

						case _MSO_1_EVENT:
							switch (param)
							{
							case _MSO_DETUNE_OCTAVE:
								for (int i = _OSC_DETUNE_MIN_OCTAVE; i <= _OSC_DETUNE_MAX_OCTAVE; i++)
								{
									max_str_list << QString::number(i);
									min_str_list << QString::number(i);
								}
								break;

							case _MSO_DETUNE_SEMITONES:
								for (int i = _OSC_DETUNE_MIN_SEMITONES; i <= _OSC_DETUNE_MAX_SEMITONES; i++)
								{
									max_str_list << QString::number(i);
									min_str_list << QString::number(i);
								}
								break;

							case _MSO_DETUNE_CENTS:
								for (int i = 4 * _OSC_DETUNE_MIN_CENTS; i <= 4 * _OSC_DETUNE_MAX_CENTS; i++)
								{
									// 0.25 steps
									max_str_list << QString::number(i / 4.f);
									min_str_list << QString::number(i / 4.f);
								}
								break;

							case _MSO_FREQ_MOD_LFO:
							case _MSO_AMP_MOD_LFO:
								max_str_list << "None"
											 << "LFO 1" << "LFO 1 0.5sec" << "LFO 1 1sec" << "LFO 1 1.5sec" << "LFO 1 2sec"
											 << "LFO 2" << "LFO 2 0.5sec" << "LFO 2 1sec" << "LFO 2 1.5sec" << "LFO 2 2sec"
											 << "LFO 3" << "LFO 3 0.5sec" << "LFO 3 1sec" << "LFO 3 1.5sec" << "LFO 3 2sec"
											 << "LFO 4" << "LFO 4 0.5sec" << "LFO 4 1sec" << "LFO 4 1.5sec" << "LFO 4 2sec"
											 << "LFO 5" << "LFO 5 0.5sec" << "LFO 5 1sec" << "LFO 5 1.5sec" << "LFO 5 2sec"
											 << "LFO 6" << "LFO 6 0.5sec" << "LFO 6 1sec" << "LFO 6 1.5sec" << "LFO 6 2sec";

								min_str_list << "None" << "LFO 1" << "LFO 1 0.5sec" << "LFO 1 1sec" << "LFO 1 2sec"
											 << "LFO 2" << "LFO 2 0.5sec" << "LFO 2 1sec" << "LFO 2 1.5sec" << "LFO 2 2sec"
											 << "LFO 3" << "LFO 3 0.5sec" << "LFO 3 1sec" << "LFO 3 1.5sec" << "LFO 3 2sec"
											 << "LFO 4" << "LFO 4 0.5sec" << "LFO 4 1sec" << "LFO 4 1.5sec" << "LFO 4 2sec"
											 << "LFO 5" << "LFO 5 0.5sec" << "LFO 5 1sec" << "LFO 5 1.5sec" << "LFO 5 2sec"
											 << "LFO 6" << "LFO 6 0.5sec" << "LFO 6 1sec" << "LFO 6 1.5sec" << "LFO 6 2sec";

								break;

							case _OSC_FREQ_MOD_ENV:
							case _OSC_AMP_MOD_ENV:
								max_str_list << "None" << "ADSR 1" << "ADSR 2" << "ADSR 3" << "ADSR 4" << "ADSR 5" << "ADSR 6";
								min_str_list << "None" << "ADSR 1" << "ADSR 2" << "ADSR 3" << "ADSR 4" << "ADSR 5" << "ADSR 6";
								break;
							}
						}						
					}

					else
					{
						MAX_str = QString::number(MAX);
						MIN_str = QString::number(MIN);
					}

					// Open the parameters selection dialog				
					Dialog_SelectMLtrainingParam *dialog = new Dialog_SelectMLtrainingParam(
						this, 
						module_name, 
						submodule_name, 
						param_name, 
						MAX_str, 
						MIN_str, 
						max, 
						min, 
						mode, 
						type,
						max_str_list,
						min_str_list);

					MainWindow::active_ml_param_dialog = dialog; // Track it

					// Clear the pointer when dialog is closed
					connect(dialog, &QDialog::finished, [this]() {
						MainWindow::active_ml_param_dialog = nullptr;
					});
					
					dialog->setAttribute(Qt::WA_DeleteOnClose); // Ensure dialog is deleted when closed
					dialog->show();

					// For combobox, consume the event to prevent popup from opening
					if (type == _WIDGET_TYPE_COMBOBOX)
					{
						return true; // Event consumed - don't pass to combobox
					}
				}
			}
		}
	}

	// Pass the event to the base class
	return QMainWindow::eventFilter(watched, event);
}

void MainWindow::add_new_ml_iterare_parm_min_max_values()
{
	if (widgets_selection_active)
	{
		ml_training_params_list.push_back(param_info);
	}
}