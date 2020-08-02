# Instructions

Build and use Docker for the runtime environment.

```
$ docker build -t nodejs-benchmark:v1 .
$ docker run --rm -it -v $(pwd):/app nodejs-benchmark:v1
(docker) $ cd /app
```

```
(docker) $ node fannkuchredux.node-5.js 12
(docker) $ node nbody.node-6.js 50000000
(docker) $ node binarytrees-node-7.js 21
(docker) $ node mandelbrot.node-3.js 15000
(docker) $ node fasta.node-1.js 25000000
```
