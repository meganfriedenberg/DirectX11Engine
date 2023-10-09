# DirectX11Engine
Features shaders, multi-threading, an asset pipeline from Blender. It also features 3D collision detection, skeletal animation, normal mapping, multiple render targets, mipmapping, and billboarding.

- [Graphics pipeline](https://github.com/meganfriedenberg/DirectX11Engine/blob/main/DX11E/Source/game.cpp) is set up and rendered every frame using a multi render target Bloom Mask and deferred rendering by doing individual passes for diffuse, normals, and positions.

- [Skeletal animation](https://github.com/meganfriedenberg/DirectX11Engine/blob/main/DX11E/Engine/Animation.cpp) is done through SLERP and computing inverse bind pose matrices.

- [Asset pipeline](https://github.com/meganfriedenberg/DirectX11Engine/blob/main/DX11E/Engine/mesh.cpp) is done by exporting meshes out of Blender to match the asset format read into the engine. 


![GIF of a character running around in the game engine.](https://github.com/meganfriedenberg/meganfriedenberg.github.io/blob/master/images/485engine.gif?raw=true)   