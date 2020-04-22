'use strict';

let workers = new Array(4).fill(null);

// for Nested Worker
let worker = null;

let runWebWorkers    = true;
let runNestedWorkers = true;

function drawVideoOnCanvasByWebWorkers(video, canvas, src, dest) {
  const { width, height } = canvas;

  src.drawImage(video, 0, 0, width, height);

  if (runWebWorkers) {
    workers.forEach((worker) => {
      if (worker) {
        worker.terminate();
        worker = null;
      }

      worker = new Worker('./workers/web-worker.js');

      worker.postMessage({
        input : src.getImageData(0, 0, width, height),
        output: dest.createImageData(width, height)
      });;

      worker.onmessage = (event) => {
        dest.putImageData(event.data, 0, 0);

        dest.font = '16px Arial';
        dest.fillStyle = '#fff';
        dest.fillText('Web Workers', 12, 24);
      }
    });
  } else {
    workers.forEach((worker) => {
      if (worker) {
        worker.terminate();
        worker = null;
      }
    });
  }

  requestAnimationFrame(() => {
    drawVideoOnCanvasByWebWorkers(video, canvas, src, dest);
  });
}

function drawVideoOnCanvasByNestedWorker(video, canvas, src, dest) {
  const { width, height } = canvas;

  src.drawImage(video, 0, 0, width, height);

  if (runNestedWorkers) {
    worker = new Worker('./workers/nested-worker.js');

    worker.postMessage({
      input : src.getImageData(0, 0, width, height),
      output: dest.createImageData(width, height)
    });;

    worker.onmessage = (event) => {
      dest.putImageData(event.data, 0, 0);

      dest.font = '16px Arial';
      dest.fillStyle = '#fff';
      dest.fillText('Nested Workers', 12, 24);
    }
  } else {
    if (worker) {
      worker.terminate();
      worker = null;
    }
  }

  requestAnimationFrame(() => {
    drawVideoOnCanvasByNestedWorker(video, canvas, src, dest);
  });
}

fetch('https://weblike-curtaincall.ssl-lolipop.jp/portfolio-music-v/video/silentjealousy_mix.mp4')
  .then((response) => response.blob())
  .then((blob) => {
    const video = document.querySelector('video');

    video.src = window.URL.createObjectURL(blob);

    const canvas              = document.getElementById('canvas-src');
    const canvasWebWorkers    = document.getElementById('canvas-web-workers');
    const canvasNestedWorkers = document.getElementById('canvas-nested-workers');

    const context              = canvas.getContext('2d');
    const contextWebWorkers    = canvasWebWorkers.getContext('2d');
    const contextNestedWorkers = canvasNestedWorkers.getContext('2d');

    canvas.classList.add('-loaded');

    canvas.addEventListener('click', () => {
      if (video.paused) {
        video.play();
        drawVideoOnCanvasByWebWorkers(video, canvas, context, contextWebWorkers);
        drawVideoOnCanvasByNestedWorker(video, canvas, context, contextNestedWorkers);
      }
    });
  });
