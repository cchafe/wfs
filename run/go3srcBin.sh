ssr-binaural  --hrirs xxx.wav bin.asd --end-of-message-character=10 --ip-server=5000 &
sleep 2
jmess -D
cd ../ck; chuck  --channels:3 --chugin-path:../qt/ssr/  --caution-to-the-wind ssr3SndBufs-jmess.ck

# ecasound -i rad.wav -o jack,WFS-Renderer:in_1

