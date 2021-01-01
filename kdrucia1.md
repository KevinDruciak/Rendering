Assignment 3: OpenGL Rendering
------------------------------

###### Kevin Druciak

kdrucia1

Late Days: 0

MSVC / Visual Studio Community 2017 / Windows 10

#### Summary: {#summary-}

I unfortunately only had time to implement the basic features for this
assignment. Ideally, I would have liked to implement acceleration and
Phong shading. Gouraud shading leaves a lot to be desired. Although I am
able to render different shapes rather nicely, the lack of nicer aspects
of the ray tracer leaves a lot of the images looking rather flat.

#### Implemented Features: {#implemented-features-}

-   all lights
-   all camera operations
-   all shapes
-   affine transformations
-   textures for sphere, triangle, box, torus
-   interactable objects
-   scene ray tracing

#### Unimplemented Features: {#unimplemented-features-}

-   anti-aliasing
-   buffer object rendering
-   glsl lighting
-   transparency, reflections, shadows, robotic arm

#### Modifications to original code base: {#modifications-to-original-code-base-}

-   box.h
    -   pre-compute texture, index, vertex, and normal coordinates
-   light.h + child classes
    -   added virtual method "drawOpenGLoff" to draw ambient lighting
        when lights are turned off
-   scene.cpp
    -   modified "Scene::drawOpenGL" to draw off/on lights
-   scene.h
    -   added "lightsOn" field to keep track of whether lights are
        on/off
-   scene.todo.cpp
    -   modified "getColor" header to draw lights
-   shape.h + child classes
    -   added virtual method "implemented" to track if a shape is able
        to be raytraced (it has an intersect implementation)
-   window.cpp + window.h
    -   declare static variable lightsON to track light status
    -   declare static variable SceneName to track the name of the scene
        .ray file
    -   Window::MouseFunction
        -   I implemented the interactable object functionality here. I
            first get a ray from the camera and intersect the scene. I
            check if the object I intersect with has a material with a
            string identifier such as "button" or door. For the button,
            I simply invert the global light tracking variable which in
            turn turns off the lights. Opening and closing the door was
            a bit trickier than I had expected so I opted for the naïve
            solution. If my ray intersects with the door, I first check
            the name of the current scene ray file. I then create a new
            scene from a brand new ray file with the door opened/closed
            and render it. Naturally, this is a pretty slow function,
            but it works for now.

#### Ray::ShapeList::drawOpenGL {#ray-shapelist-drawopengl}

-   calls "drawOpenGL" for all shapes in the list

#### Ray::TriangleList::drawOpenGL {#ray-trianglelist-drawopengl}

-   calls "drawOpenGL" on the shapelist and sets material

#### Ray::Material::drawOpenGL {#ray-material-drawopengl}

-   calls "initOpenGL" for texture. I have to generate a new texture on
    every draw call. I'm sure there's a better way to do this. I also
    check the global variable "Window::lightsON" when generating the
    emissive property in order to simulating a light turning on and off.

#### Ray::Light::drawOpenGL/drawOpenGLoff {#ray-light-drawopengl-drawopengloff}

-   similar to assignment 2 for "drawOpenGL". In "drawOpenGLoff" I
    simulate the light being off by setting all of its properties to 0
    except for ambient.

#### Ray::AffineShape::drawOpenGL {#ray-affineshape-drawopengl}

-   I couldn't find a way to pass the type Matrix4D from "getMatrix"
    into the "glMultMatrixf" call so I had to copy it into an array

#### Ray::Triangle::drawOpenGL {#ray-triangle-drawopengl}

-   used Plane for normals, and vertices for texture/position

#### Ray::Texture::initOpenGL {#ray-texture-initopengl}

-   simply texture init

#### Ray::Box::drawOpenGL {#ray-box-drawopengl}

-   I first precompute the textures/indices/normals/vertices in the
    "initOpenGL" method and iterate iterate over the faces of the box,
    drawing them with GL\_QUADS.

![0](kdrucia1_HTML/box.bmp)

#### Ray::Cylinder::drawOpenGL {#ray-cylinder-drawopengl}

-   draw body with parametric equations for a cylinder using
    TRIANGLE\_STRIP, then endcaps using GL\_TRIANGLE\_FAN

![1](kdrucia1_HTML/cylinder.bmp)

#### Ray::Cone::drawOpenGL {#ray-cone-drawopengl}

-   I figured that the best way to draw a roof for my room scene was to
    use an OpenGLTessellationComplexity of 4 (which is a rectangular
    pyramid) so I check if the material that I am rendering a roof first
    and set the OpenGLTessellationComplexity accordingly. The cone
    itself is a GL\_TRIANGLE\_FAN with the first vertex as the peak. The
    base is a GL\_TRIANGLE\_FAN circle.

![2](kdrucia1_HTML/cone.bmp)

#### Ray::Torus::drawOpenGL {#ray-torus-drawopengl}

-   The torus vertices were generated from a torus's parametric
    equations. I was having trouble finding normals to the torus and
    eventually consulted the following resource:
    [http://www.cosinekitty.com/raytrace/chapter13\_torus.html](http://www.cosinekitty.com/raytrace/chapter13_torus.html).

![3](kdrucia1_HTML/torus.bmp)

Fun fact: I couldn't find a texture that mapped properly onto the torus,
so I made my own donut texture in microsoft paint!

#### Ray::Sphere::drawOpenGL {#ray-sphere-drawopengl}

-   Parametric equations for vertices. I render four vertices at a time
    in order to be able to create tex coordinates for GL\_QUAD\_STRIP.

![4](kdrucia1_HTML/chessboard.bmp)

Here is the OpenGL rendering version of my assignment 2 art submission.
It is compared to the ray traced version below.

![5](kdrucia1_HTML/chessboardraytraced.bmp)

#### Room: {#room-}

![6](kdrucia1_HTML/room1.bmp)

![7](kdrucia1_HTML/room2.bmp)

![8](kdrucia1_HTML/room3.bmp)

![9](kdrucia1_HTML/room4.bmp)

![10](kdrucia1_HTML/room5.bmp)

Here, we can see, in order, closed door, open door, lights on, lights
off, and the flashlight.

#### Ray Traced Scene: {#ray-traced-scene-}

![11](kdrucia1_HTML/davidopengl.bmp)

![12](kdrucia1_HTML/david1.bmp)

The first image is the OpenGL rendering of david.ray. The second is the
ray-traced scene from the same perspective of the current OpenGL
context.

#### Art Submission: {#art-submission-}

![13](kdrucia1_HTML/kdrucia1.art/kdrucia1.art.3.bmp)

I submit this image and its ray file, "kdrucia1.art.3.ray" as my art
submission.
