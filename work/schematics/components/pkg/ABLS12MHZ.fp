# element_flags, description, name, value, mark_x, mark_y,
# text_x, text_y, text_dir, text_scale, text_flags
Element["" "ABLS 12MHz Crystal SMD pads" "" "abls12mhz" 0 0 0 0 0 100 ""]
(
	#Pad [x1 y1 x2 y2 Thickness Clearance Mask "Name" "Number" SFlags]
	Pad[-0.15mm  2.35mm
	     3.35mm  2.35mm
		2.1mm 2000 4600 "1" "1" "square"]
	Pad[ 9.35mm  2.35mm
	    12.85mm  2.35mm
		2.1mm 2000 4600 "2" "2" "square"]

	# Outline
	# ElementLine [ x1 y1 x2 y2 w ]
	ElementLine[0mm 0mm 12.7mm 0mm 0.25mm]
	ElementLine[12.7mm 0mm 12.7mm 4.7mm 0.25mm]
	ElementLine[12.7mm 4.7mm 0mm 4.7mm 0.25mm]
	ElementLine[0mm 4.7mm 0mm 0mm 0.25mm]
)

