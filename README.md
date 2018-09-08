# UnityEditorGyro
The Unity Editor doesn't currently provide access to the gyroscope in the editor itself! And even if it did, we would never have access to it outside of runtime. I wrote a [blog post about this tool](http://playdeck.net/blog/accessing-the-gyroscope-in-editor), which talks a bit more about how and why I made it!

So, here's a quick plugin that gives you gyroscope access, in the editor, AND outside of runtime :)

## Getting Started

You can download a [prebuilt .unitypackage here](https://github.com/maluoi/UnityEditorGyro/tree/master/Downloads)!

Once it's imported to your project, you can just call **EditorGyro.GetRotation()**. In editor it will use the provided DLLs, and in builds it'll fall back to Input.gyro.attitue automatically!

Check out FollowGyroscope for an example usage. FollowGyroscope can also be attached to your camera to simulate VR headset, or phone AR rotation!

## Repository Organization

This repository includes: 
1. [a C++ DLL project that accesses sensors](https://github.com/maluoi/UnityEditorGyro/tree/master/DLLProject)
2. [a Unity Plugin project that accesses the DLL](https://github.com/maluoi/UnityEditorGyro/tree/master/UnityProject)
3. and a [download folder with the final unitypackages](https://github.com/maluoi/UnityEditorGyro/tree/master/Downloads)
