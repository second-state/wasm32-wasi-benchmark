# Instructions

Build and use Docker for the runtime environment.

```
$ docker build -t nodejs-benchmark:v1 .
$ docker run --rm -it -v $(pwd):/app nodejs-benchmark:v1
(docker) $ cd /app
```

Run tests interactively

```
(docker) $ time node nop.js
(docker) $ time node cat-sync.js
(docker) $ time node fannkuchredux.node-5.js 12
(docker) $ time node nbody.node-6.js 50000000
(docker) $ time node binarytrees-node-7.js 21
(docker) $ time node mandelbrot.node-3.js 15000
(docker) $ time node fasta.node-1.js 25000000
```

Performance

```
$ time docker run --cpus="1.0" --rm -v $(pwd):/app -w /app -i -t nodejs-benchmark:v1 node nop.js
$ time docker run --cpus="1.0" --rm -v $(pwd):/app -w /app -i -t nodejs-benchmark:v1 node cat-sync.js
$ time docker run --cpus="1.0" --rm -v $(pwd):/app -w /app -i -t nodejs-benchmark:v1 node fannkuchredux.node.js 12
$ time docker run --cpus="1.0" --rm -v $(pwd):/app -w /app -i -t nodejs-benchmark:v1 node nbody.node-6.js 50000000
$ time docker run --cpus="1.0" --rm -v $(pwd):/app -w /app -i -t nodejs-benchmark:v1 node binarytrees-node-7.js 21
$ time docker run --cpus="1.0" --rm -v $(pwd):/app -w /app -i -t nodejs-benchmark:v1 node mandelbrot.node-3.js 15000
$ time docker run --cpus="1.0" --rm -v $(pwd):/app -w /app -i -t nodejs-benchmark:v1 node fasta.node-1.js 25000000
```
