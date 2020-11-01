# lab1-planets

### Compile:

```
$ make
```

### Generate map with %n% planets (%n% > 1):
```
$ ./game gen %n%
```

For example:


```
$ ./game gen 3
```

This will generate file *map.bin* in current directory. This is serialized data about planets and portals between them.

### Load map:

```
$ ./game load map.bin
```