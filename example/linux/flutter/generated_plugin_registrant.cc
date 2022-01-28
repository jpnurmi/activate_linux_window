//
//  Generated file. Do not edit.
//

// clang-format off

#include "generated_plugin_registrant.h"

#include <activate_window/activate_window_plugin.h>

void fl_register_plugins(FlPluginRegistry* registry) {
  g_autoptr(FlPluginRegistrar) activate_window_registrar =
      fl_plugin_registry_get_registrar_for_plugin(registry, "ActivateWindowPlugin");
  activate_window_plugin_register_with_registrar(activate_window_registrar);
}
