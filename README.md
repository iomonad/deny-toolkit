# Dény Toolkit

<p align="center">
  <img src="https://raw.githubusercontent.com/iomonad/deny-toolkit/master/.github/scad_gen.png?token=ADKNHH5MF7QDBGNLNNQH2GK7LDDTS">
</p>

`deny-toolkit` is a small project that contains various tools for archiving, visualization and fuzzing purposes of Dény® key bitting.

## Repo structure 

#### `descriptor/`

Small software that render a closeup on a key image that prompt user to draw lines arround the bitting of the key in order to generate a binary file, nammed 'key descriptor' wich is the filetype used for other software like generator & collision search.

#### `dumper/`

Dump informatation of the descriptor file.

#### `openscad/`

Boilerplate for the OpenSCAD generation part. Contains base 3D model.

#### `samples/`

Some samples of descriptor & key bitting (Asset folder)

## Preparing environment

### C++ dependencies

> OpencCV4(+)

```bash
emerge -av media-libs/opencv
```

### Software dependencies

> OpenSCAD for 3D model generation visualization
```bash
emerge -av media-gfx/openscad
```

## Disclaimer

This project is not affiliated, associated, authorized, endorsed by, or in any way officially connected with the Dény® Trademark, or any of its subsidiaries or its affiliates. The official Dény® Trademark website can be found at https://www.deny-security.com.

The names Dény® as well as related names, marks, emblems and images are registered trademarks of their respective owners.

## License
[MIT](https://choosealicense.com/licenses/mit/)
