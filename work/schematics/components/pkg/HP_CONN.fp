# element_flags, description, name, value, mark_x, mark_y,
# text_x, text_y, text_dir, text_scale, text_flags
Element["" "Pads to solder the headphone connections to" "" "hp_conn" 0 0 0 0 0 100 ""]
(
	#Pad [x1 y1 x2 y2 Thickness Clearance Mask "Name" "Number" SFlags]
	Pad[ 2.50mm  2.50mm
	     2.50mm  2.50mm
		3mm 2000 4600 "1" "1" "square"]
	Pad[ 7.00mm  2.50mm
	     7.00mm  2.50mm
		3mm 2000 4600 "2" "2" "square"]
	Pad[12.50mm  2.50mm
	    12.50mm  2.50mm
		3mm 2000 4600 "3" "3" "square"]

	# Outline
	# ElementLine [ x1 y1 x2 y2 w ]
	ElementLine[0mm 0mm 15mm 0mm 0.25mm]
	ElementLine[15mm 0mm 15mm 5mm 0.25mm]
	ElementLine[15mm 5mm 0mm 5mm 0.25mm]
	ElementLine[0mm 5mm 0mm 0mm 0.25mm]
)

