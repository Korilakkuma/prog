'use strict';

const video = document.querySelector('video');

if (Hls.isSupported()) {
    const hls = new Hls({ debug : true });

    hls.loadSource('./ts/forever-love-piano-instruments.m3u8');
    hls.attachMedia(video);

    hls.on(Hls.Events.MANIFEST_PARSED, () => {
        video.play();
    });
} else if (video.canPlayType('application/vnd.apple.mpegurl')) {
    video.src = './ts/forever-love-piano-instruments.m3u8';
    video.addEventListener('loadedmetadata', () => {
        video.play();
    });
}
