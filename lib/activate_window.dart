
import 'dart:async';

import 'package:flutter/services.dart';

class ActivateWindow {
  static const MethodChannel _channel = MethodChannel('activate_window');

  static Future<String?> get platformVersion async {
    final String? version = await _channel.invokeMethod('getPlatformVersion');
    return version;
  }
}
