const NUMBER_OF_ELEMENTS = 9;

self.onmessage = (event) => {
  const { input, output } = event.data;

  // Blur (Much cost processing ...)

  // [(left-top), (top), (right-top), (left), (center), (right), (left-bottom), (bottom), (right-bottom)]
  let indexs = new Array(NUMBER_OF_ELEMENTS);
  let sum    = 0;
  let num    = 0;
  let width  = 512;  // Hard coding ...
  let blur   = 8;

  while (blur-- > 0) {
    for (let i = 0, len = input.data.length; i < len; i++) {
      indexs = [(i - 4 - 4 * width), (i - 4 * width), (i + 4 - 4 * width),
                (i - 4),             (i),             (i + 4),
                (i - 4 + 4 * width), (i + 4 * width), (i + 4 + 4 * width)];

      // Clear previous value
      sum = 0;
      num = 0;

      for (let j = 0; j < NUMBER_OF_ELEMENTS; j++) {
        if ((indexs[j] >= 0) && (indexs[j] < input.data.length)) {
          sum += input.data[indexs[j]];
          num++;
        }
      }

      output.data[i] = Math.floor(sum / num);
    }
  }

  self.postMessage(output);
};
