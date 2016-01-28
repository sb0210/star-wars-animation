cd frames
mogrify -flip -format jpg frame_*.ppm
mencoder mf://*.jpg -mf w=512:h=512:fps=25:type=jpg -ovc copy -oac copy -o ../animation.avi
cd ..
