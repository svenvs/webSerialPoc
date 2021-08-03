let port;
let lineReader;

const statusElm = document.querySelector('span');
const askButton = document.querySelector('#ask');
const textareaElm = document.querySelector('textarea');
const formElm = document.querySelector('form');

askButton.addEventListener('click', ()=> {
  port = navigator.serial.requestPort();
})

formElm.addEventListener('submit', (e)=> {
  e.preventDefault();
  console.log(e);
})


navigator.serial.addEventListener('connect', async (e) => {
    statusElm.innerText='connected';
});
// await lineReader.read()
async function readTheLines(){
    port = await getports();
    port = port[0];
    if(port){
        await port.open({ baudRate: 9600 });
        lineReader = port.readable
            .pipeThrough(new TextDecoderStream())
            .pipeThrough(new TransformStream(new LineBreakTransformer()))
            .getReader();
    }
}

navigator.serial.addEventListener('disconnect', (e) => {
    statusElm.innerText='disconnected';
});

async function getports(){
    return navigator.serial.getPorts();
}
class LineBreakTransformer {
    constructor() {
      this.container = '';
    }
  
    transform(chunk, controller) {
      this.container += chunk;
      const lines = this.container.split('\r\n');
      this.container = lines.pop();
      lines.forEach(line => controller.enqueue(line));
    }
  
    flush(controller) {
      controller.enqueue(this.container);
    }
  }

async function init(){
    readTheLines();
}
init();