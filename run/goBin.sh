ssr-binaural  --hrirs xxx.wav onePointSrc.asd --end-of-message-character=10 --ip-server=5000 &
sleep 2
jmess -D
cd ../ck; chuck  --channels:3 --chugin-path:../qt/ssr/  --caution-to-the-wind ssrSndBuf-jmess.ck

# ecasound -i rad.wav -o jack,WFS-Renderer:in_1

