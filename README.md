# ofxControlOSC 

ofxControlOSC is an OpenFrameworks addon which allows you to create interface layouts for the iOS/Android OSC-sending app [Control](http://charlie-roberts.com/Control/). 

Control is similar to [TouchOSC](http://hexler.net/software/touchosc) but has several nice features, including additional widgets not found in TouchOSC and the ability to specify custom layouts using Json.  

This addon allows you to design layouts and then generate the Json string. You can then upload it to the web and load it from the URL on the Control app, or automatically push it to your phone via OSC (note: there seems to be a bug that causes Control to crash if you try to upload a layout with multiple pages).

Note: not all widgets are supported yet -- just buttons, sliders, and multi-buttons (matrix) and multi-sliders. Knobs, multitouch, and others are forthcoming.

See the example for usage details.


### To-do / feature requests
 - Finish remaining widgets.
 - Convert an ofxUICanvas to a ControlOSC interface, and communicate between them automatically via osc.
 - Generate positioning details of widgets automatically. 
