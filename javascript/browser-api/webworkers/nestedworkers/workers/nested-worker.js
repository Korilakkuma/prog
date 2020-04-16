const NUMBER_OF_ELEMENTS = 9;

self.onmessage = (event) => {
  const { input, output } = event.data;

  let workers = new Array(3).fill(null);

  workers.forEach((worker) => {
    if (worker) {
      worker.terminate();
      worker = null;
    }

    worker = new Worker('./child-worker.js');

    worker.postMessage({ input, output });

    worker.onmessage = (event) => {
      self.postMessage(event.data);
    }
  });
};
