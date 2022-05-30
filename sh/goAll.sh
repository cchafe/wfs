# ./ssr-wfs  --hrirs xxx.wav -s line_setup.asd line_scene.asd &
./ssr-wfs  --hrirs xxx.wav -s 64WFSoutputs.asd line_scene.asd &
sleep 3
chuck --channels:3  --caution-to-the-wind all-jmess.ck 

# ecasound -i rad.wav -o jack,WFS-Renderer:in_1

