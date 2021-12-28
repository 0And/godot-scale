tool
extends EditorPlugin

func _enter_tree():
	add_custom_type("Scale", "Control", preload("scale.gd"), preload("icon_scale.svg"))

func _exit_tree():
	remove_custom_type("Scale")