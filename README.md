# MVC Cloning

Seamless cloning based on Mean-Value Coordinates (MVC).

## How to use

### Compile

``` bash
make
```

### Run

Put pictures named `[project]_target.jpg` and `[project]_source.jpg` under `images/`. The edge info is saved in `[project].txt` in `edge/` folder.

Run under folder `bin/`:

``` bash
./demo [project]
```

Parameter project must be the same as the name of picture and edge txt.

The result picture and the adaptive mesh picture will be saved under `result/`.

## Reference

Z. Farbman, G. Hoffer, Y. Lipman, D. Cohen-Or, D. Lischinski, Coordinates for Instant Image Cloning, ACM SIGGAPH 2009