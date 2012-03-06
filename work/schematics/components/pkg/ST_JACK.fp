# element_flags, description, name, value, mark_x, mark_y,
# text_x, text_y, text_dir, text_scale, text_flags
Element["" "Stereo 3.5mm Jack" "" "st_jack" 0 0 0 0 0 100 ""]
(
	#Pin[x y thickness clearance mask drillholedia name number flags]
	Pin[10.5mm 1.5mm 6000 2000 7000 3500 "" "1" "edge2"]
	Pin[11.8mm 10.5mm 6000 2000 7000 3500 "" "2" "edge2"]
	Pin[2.5mm 8.2mm 6000 2000 7000 3500 "" "3" "edge2"]
	Pin[9.5mm 8.4mm 6000 2000 7000 3500 "" "" "edge2"]
	
	# Outline
	# ElementLine [ x1 y1 x2 y2 w ]
	ElementLine[0mm 0mm 12mm 0mm 0.25mm]
	ElementLine[12mm 0mm 12mm 12mm 0.25mm]
	ElementLine[12mm 12mm 0mm 12mm 0.25mm]
	ElementLine[0mm 12mm 0mm 9mm 0.25mm]
	ElementLine[0mm 3mm 0mm 0mm 0.25mm]
)
