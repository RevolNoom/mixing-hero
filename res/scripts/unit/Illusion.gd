extends Node2D

signal mouse_event 
signal mouse_exited

# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_MouseCapture_mouse_exited():
	emit_signal("mouse_exited")


func _on_MouseCapture_input_event(_viewport, event, _shape_idx):
	if event is InputEventMouse:
		emit_signal("mouse_event", event)
