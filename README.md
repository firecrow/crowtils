# crowtree

A simple balanced tree with elements from red/black trees, serving as a shallow
footprint key value store.

Red and black nodes are tracked and toggled on and off as items are created,
the rotate function is very simple, we tested a few datasets and determined tha
the full red/black algorithm, while advantagous, provided little benefit to
this implemetation.
