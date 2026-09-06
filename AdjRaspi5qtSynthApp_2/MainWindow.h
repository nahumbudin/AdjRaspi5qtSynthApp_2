/**
*	@file		MainWindow.h
*	@author		Nahum Budin
*	@date		22-Sep-2025
*	@version	1.1 
*					1. Refactoring rename modules to instruments
*	
*	History:
*			Version	1.0		8-May-2024
*
*	@brief		Application Main Window that hosts the instruments pannels.
*/

#pragma once

#include <QMainWindow>
#include <QActionGroup>
#include <QAction>
#include <QDialog>
#include <QThread>

#include "libAdjRaspi5SynthAPI.h"
#include "Defs.h"
#include "InstrumentPannel.h"
#include "GuiNavigator.h"
#include "HttpBridgeQt.h"

#include "Dialog_WindowsManager.h"
#include "Dialog_SelectMLtrainingParam.h"
#include "Dialog_TrainingParamsEditor.h"

class InstrumentPannel;
class GuiNavigator;

void wrapper_closeModulePannel(en_instruments_ids_t moId);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	
	static MainWindow *get_instance();

	//static HttpBridgeQt *http_bridge;

	void close_instrument_pannel_id(en_instruments_ids_t mo_id);
	void close_instrument_pannel_name(string inst_name);
	
	void request_close_instrument_pannel_id(en_instruments_ids_t mo_id);
	void request_close_instrument_pannel_name(string inst_name);

	bool eventFilter(QObject *watched, QEvent *event) override;

	void register_widget_for_click_detection(QWidget *widget);

	InstrumentPannel *get_instrument_panel_by_id(en_instruments_ids_t inst_id);
	
	vector<string> get_active_instruments_names_list();
	
	void control_box_ui_update_callback(int evnt, uint16_t val);
	
	void register_active_dialog(QDialog *dialog);
	void unregister_active_dialog(QDialog *dialog);
	
	void on_patch_file_saved(const QString &s);
	void on_patch_file_loaded(const QString &s);
	
	void copy_sketch(int src, int dest);

	bool is_auto_arrange_enabled() const { return auto_arrange_enabled; }
	void set_auto_arrange(bool enabled);

	bool is_ml_widgets_selection_active() const { return widgets_selection_active; }
	void set_ml_widgets_selection_active(bool active);
	void clear_widgets_selection_list();

	static void add_new_ml_iterare_parm_min_max_values();

	vector<string> pending_open_instruments_list;
	
	vector<active_instrument_data_t> active_instruments_list;
	
	QMenu *sketches_menu;

	// Holds all GUI controls widgets and ML training data.
	// int[9] - Module id, submodule id, param id, 99Param MAX, MIN, max, min, fix(0)/iterate(1), type (0-dial, 1-slider, 2-combobox, 3-button, 4-checkbox)
	static std::unordered_map<QWidget *, std::array<int, 9>> widgets_map_ml_training_info;

	static std::unordered_map<int, std::string> modules_names_map;
	static std::unordered_map<int, std::string> submodules_names_map;
	static std::unordered_map<int, std::string> params_names_map;

	static std::vector<std::array<int, 8>> ml_training_params_list;

	static Dialog_SelectMLtrainingParam *active_ml_param_dialog;
	static Dialog_TrainingParamsEditor *training_params_editor_dialog;

	static std::array<int, 8> param_info;

	Dialog_WindowManager *window_manager;
	
	
public slots:
	virtual void timerEvent(); // Called by a Timer

	void show_window_manager();

	//void focusChanged(QWidget *, QWidget *now);

  private slots:
	void on_add_fluid_synth_instrument();
	void on_add_hammond_organ_instrument();
	void on_add_adj_analog_synth_instrument();
	void on_add_adj_karplus_strong_strings_synth_instrument();
	void on_add_adj_morphed_sin_synth_instrument();
	void on_add_adj_pad_synth_instrument();
	void on_add_adj_midi_player_instrument();
	void on_add_adj_reverb_effect_instrument();
	void on_add_adj_distortion_effect_instrument();
	void on_add_adj_graphic_equilizer_instrument();	
	void on_add_midi_mixer_instrument();
	void on_add_adj_midi_mapper_instrument();
	void on_add_adj_external_midi_interface_control_instrument();
	void on_add_adj_keyboard_control_instrument();
	void on_add_adj_keyboard_mapper_instrument();

	void on_save_patch_file();
	void on_load_patch_file();
	
	void on_copy_sketch1_to_sketch2();
	void on_copy_sketch1_to_sketch3();
	void on_copy_sketch2_to_sketch1();
	void on_copy_sketch2_to_sketch3();
	void on_copy_sketch3_to_sketch1();
	void on_copy_sketch3_to_sketch2();

	void on_save_active_sketch();
	void on_load_active_sketch();

	void on_open_master_volume_dialog();
	void on_open_recording_dialog();
	void on_open_http_server_dialog();

	void on_auto_arrange_toggled(bool checked);

	void on_ml_widgets_selection_toggled();
	void on_open_widgets_selction_edit_dialog();
	void on_clear_widgets_selection_list();

	void on_lfos_sync_changed(QAction *action);
	void on_midi_mapping_mode_changed(QAction *action);
	

	void on_load_synth_patch_preset_1();
	void on_load_synth_patch_preset_2();
	void on_load_synth_patch_preset_3();
	void on_load_synth_patch_preset_4();
	void on_load_synth_patch_preset_5();
	void on_load_synth_patch_preset_6();
	void on_load_synth_patch_preset_7();
	void on_load_synth_patch_preset_8();
	void on_load_synth_patch_preset_9();
	void on_load_synth_patch_preset_10();
	void on_load_synth_patch_preset_11();
	void on_load_synth_patch_preset_12();
	void on_load_synth_patch_preset_13();
	void on_load_synth_patch_preset_14();
	void on_load_synth_patch_preset_15();
	void on_load_synth_patch_preset_16();
	
protected:
//	void timerEvent(QTimerEvent *event);
	virtual void update_gui();
	void closeEvent(QCloseEvent *event) override;

	void on_preset_file_loaded(const QString &s);
	void on_preset_file_saved(const QString &s);
    

private:
	InstrumentPannel* add_instrument_pannel(QString instrument_name_string="");

	void update_add_instrument_menu_status();
	
	int remove_instrument_pannel(InstrumentPannel *instrument);
	int is_instrument_openned(en_instruments_ids_t instId);
	
	int update_layout_geometry();

	void open_synth_patch_preset_int(int preset_num);

	bool auto_arrange_enabled = true;

	static bool widgets_selection_active;

	void create_actions();
	void create_menus();

	void arrange_instrument_panels();
	int get_panel_type_order(const QString &instrument_name);
	
	void start_update_timer(int interval);

	void init_dictionaries();

	Ui::MainWindow *ui;
	static MainWindow *mwind;	
	
	QLayout *layout;

	GuiNavigator *gui_navigator;

	map<string, en_instruments_ids_t> instruments_ids_map;
	
	list<QDialog*> active_dialogs_list;
	
	QMenu *file_menu;
	QMenu *add_module_menu;
	
	QMenu *help_menu;

	
	QActionGroup *add_modules_group;
	QAction *add_fluid_synth_act;
	QAction *add_hammond_organ_act;
	QAction *add_adj_analog_synth_act;
	QAction *add_adj_karplus_strong_strings_synth_act;
	QAction *add_adj_morphed_sin_synth_act;
	QAction *add_adj_pad_synth_act;
	QAction *add_adj_midi_player_act;
	QAction *add_adj_reverb_effect_act;
	QAction *add_adj_distortion_effect_act;
	QAction *add_adj_graphic_equilizer_act;
	QAction *add_midi_mixer_act;
	QAction *add_adj_midi_mapper_act;
	QAction *add_adj_external_midi_interface_control_act;
	QAction *add_adj_keyboard_control_act;
	QAction *add_adj_keyboard_mapper_act;

	QMenu *controls_menu;
	QAction *open_master_volume_act;
	QAction *open_recording_act;
	QAction *open_http_server_act;

	// In the private section with other menu-related members
	QMenu *settings_menu;
	QActionGroup *lfos_sync_action_group;
	QAction *lfos_sync_none_act;
	QAction *lfos_sync_retrig_act;
	QAction *lfos_sync_retrig1st_act;
	QActionGroup *midi_mapping_mode_action_group;
	QAction *midi_mapping_mode_mapping_act;
	QAction *midi_mapping_mode_sketch_act;

	QActionGroup *patch_files_group;
	QAction *save_patch_file_act;
	QAction *load_patch_file_act;
	
	QActionGroup *sketches_group;
	QAction *copy_sketch1_to_sketch2_act;
	QAction *copy_sketch1_to_sketch3_act;
	QAction *copy_sketch2_to_sketch1_act;
	QAction *copy_sketch2_to_sketch3_act;
	QAction *copy_sketch3_to_sketch1_act;
	QAction *copy_sketch3_to_sketch2_act;

	QAction *save_active_sketch;
	QAction *load_active_sketch;

	QMenu *view_menu;
	QAction *auto_arrange_act;

	QMenu *widgets_selection_menu;
	QAction *toggle_widgets_selection_act;
	QAction *open_widgets_selction_edit_dialog_act;
	QAction *clear_widgets_selection_list_act;

	QMenu *synth_patches_menu;
	QAction *load_preset_actions[16];

	bool control_box_left_key_pressed = false;
	bool control_box_right_key_pressed = false;
	bool control_box_up_key_pressed = false;
	bool control_box_down_key_pressed = false;
	bool control_box_ok_key_pressed = false;
	bool control_box_scroll_select_change_value = false;
	int control_box_scroll_select_new_value = 0;
	int control_box_scroll_select_prev_value = -1;
	bool control_box_scroll_pushbutton_pressed = false;

	QString last_sketch_preset_directory = "";
	QString last_sketch_preset_load_file = "";
	QString last_sketch_preset_save_file = "";
};

class SavePatchFileThread : public QThread
{
	Q_OBJECT	
	void run();
	
signals:
	void savePatchFileDone(const QString &s);	
		
};

class LoadPatchFileThread : public QThread
{
	Q_OBJECT	
	void run();
	
signals:
	void loadPatchFileDone(const QString &s);	
		
};

class LoadPresetFileThread : public QThread
{
	Q_OBJECT
	void run();

  signals:
	void loadPresetFileDone(const QString &s);
};

class SavePresetFileThread : public QThread
{
	Q_OBJECT
	void run();

  signals:
	void savePresetFileDone(const QString &s);
};

