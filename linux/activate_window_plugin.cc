#include "include/activate_window/activate_window_plugin.h"

#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>
#include <sys/utsname.h>

#include <cstring>

#define ACTIVATE_WINDOW_PLUGIN(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), activate_window_plugin_get_type(), \
                              ActivateWindowPlugin))

struct _ActivateWindowPlugin {
  GObject parent_instance;
};

G_DEFINE_TYPE(ActivateWindowPlugin, activate_window_plugin, g_object_get_type())

// Called when a method call is received from Flutter.
static void activate_window_plugin_handle_method_call(
    GtkWidget* window,
    FlMethodCall* method_call) {
  g_autoptr(FlMethodResponse) response = nullptr;

  const gchar* method = fl_method_call_get_name(method_call);

  if (strcmp(method, "activateWindow") == 0) {
    gtk_window_present_with_time(GTK_WINDOW(window), GDK_CURRENT_TIME);
    response = FL_METHOD_RESPONSE(fl_method_success_response_new(nullptr));
  } else {
    response = FL_METHOD_RESPONSE(fl_method_not_implemented_response_new());
  }

  fl_method_call_respond(method_call, response, nullptr);
}

static void activate_window_plugin_dispose(GObject* object) {
  G_OBJECT_CLASS(activate_window_plugin_parent_class)->dispose(object);
}

static void activate_window_plugin_class_init(ActivateWindowPluginClass* klass) {
  G_OBJECT_CLASS(klass)->dispose = activate_window_plugin_dispose;
}

static void activate_window_plugin_init(ActivateWindowPlugin* self) {}

static void method_call_cb(FlMethodChannel* channel, FlMethodCall* method_call,
                           gpointer user_data) {
  GtkWidget* window = GTK_WIDGET(user_data);
  activate_window_plugin_handle_method_call(window, method_call);
}

void activate_window_plugin_register_with_registrar(FlPluginRegistrar* registrar) {
  ActivateWindowPlugin* plugin = ACTIVATE_WINDOW_PLUGIN(
      g_object_new(activate_window_plugin_get_type(), nullptr));

  FlView* view = fl_plugin_registrar_get_view(registrar);
  GtkWidget* window = gtk_widget_get_toplevel(GTK_WIDGET(view));

  g_autoptr(FlStandardMethodCodec) codec = fl_standard_method_codec_new();
  g_autoptr(FlMethodChannel) channel =
      fl_method_channel_new(fl_plugin_registrar_get_messenger(registrar),
                            "activate_window",
                            FL_METHOD_CODEC(codec));
  fl_method_channel_set_method_call_handler(channel, method_call_cb,
                                            window,
                                            nullptr);

  g_object_unref(plugin);
}
