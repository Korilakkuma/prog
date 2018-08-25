'use strict';

class MSE {
    constructor(video, file) {
        this.video = video;
        this.file  = file;

        this.initVideo();
    }

    initVideo() {
        if (!MediaSource.isTypeSupported('video/webm; codecs="vp8,vorbis"')) {
            return;
        }

        this.mediaSource = new MediaSource();
        this.mediaSource.addEventListener('sourceopen', this.initSourceBuffer.bind(this), false);

        this.video.src = window.URL.createObjectURL(this.mediaSource);

        // if ('srcObject' in video) {
        //     video.srcObject = this.mediaSource;
        // } else {
        //     video.src = window.URL.createObjectURL(this.mediaSource);
        // }
    }

    initSourceBuffer() {
        this.sourceBuffer = this.mediaSource.addSourceBuffer('video/webm; codecs="vp8,vorbis"');
        this.sourceBuffer.addEventListener('updateend', () => {
            if (!this.sourceBuffer.updating && (this.mediaSource.readyState === 'open')) {
                this.mediaSource.endOfStream();
            }
        }, false);

        this.appendSegment();
    }

    appendSegment() {
        const xhr = new XMLHttpRequest();

        xhr.open('GET', this.file, true);
        xhr.responseType = 'arraybuffer';
        xhr.onload = () => this.sourceBuffer.appendBuffer(xhr.response);
        xhr.send(null);
    }
}

const mse = new MSE(document.querySelector('video'), 'kurenai-twin.webm');
