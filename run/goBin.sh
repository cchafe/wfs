ssr-binaural  --hrirs xxx.wav onePointSrc.asd --end-of-message-character=10 --ip-server=5000 &
sleep 2
jmess -D
//chuck --channels:3 --caution-to-the-wind ../ck/oneSndBuf-jmess.ck 

# ecasound -i rad.wav -o jack,WFS-Renderer:in_1

