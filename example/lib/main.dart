import 'dart:async';

import 'package:flutter/services.dart';
import 'package:flutter/material.dart';

const methodChannel = MethodChannel('activate_window');

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  void _activateWindowLater() {
    Timer(const Duration(seconds: 3), () {
      methodChannel.invokeMethod('activateWindow');
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Activate Linux window'),
        ),
        body: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              const Text('1. Click the button and switch to another app.'),
              const SizedBox(height: 16),
              const Text('2. A window activation request is sent in 3s.'),
              const SizedBox(height: 48),
              ElevatedButton(
                onPressed: _activateWindowLater,
                child: const Text('Activate'),
              ),
              const SizedBox(height: 48),
            ],
          ),
        ),
        bottomNavigationBar: const Padding(
          padding: EdgeInsets.all(16.0),
          child: Text(
            // https://gitlab.gnome.org/GNOME/gtk/-/issues/624
            'It is up to the window manager to decide whether the window '
            'activation request is handled by bringing the window to front, '
            'or by showing a "the app is ready" banner (most likely the latter).',
          ),
        ),
      ),
    );
  }
}
