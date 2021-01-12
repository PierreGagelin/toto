# Video streaming using HTTP

The goal is to stream a video though HTTP with VLC and display it on a web browser using only HTML

## HTTP streaming

In order to stream the video to HTTP with VLC, use the following command:

- cvlc video.mp4 --sout '#transcode{vcodec=theo,vb=800,acodec=vorb,ab=128,channels=2,samplerate=44100,scodec=none}:http{mux=ogg,dst=:8080/vlc_video}'

## HTML video display

In order to display the video that VLC streams, open page.html with a web browser:

- firefox page.html
- chromium page.html
