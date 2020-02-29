# SpeedCC
---

A rapid and powerful development framework in C++ for cocos2d-x and targets for mobile game building. It can help developer to focus on the game logic without paying more attention on complicate code setup.

**Highlight Features:**
* 	Productive
*	Lightweight Thinking
*	High Performance
*	Elegance  
  
    

---

### Productive
SpeedCC re-defines programming model for game building, so it integrates features organically, every feature works with another feature together in order to provide huge efficiency improvement for game development, it can reduce development time dramatically. 

### Buiding Scene in Hierarchy

The best balance solution to build scene with code between statically and dynamically, it can combine with **Data Binding** to save plenty of time in development.

```c++
SC_BEGIN_PARENT_ROOT(nullptr,SCWinSize)
    SC_INSERT_LABEL(nullptr,"dock=top|mid-x; y-by=-10;","Title","",20)
    SC_INSERT_SPRITE(nullptr,"dock=center;","HelloWorld.png")

    SC_BEGIN_PARENT_LAYER_COLOR(nullptr, "dock=bottom|right;", Size(80,40), Color4B::BLUE)
        SC_INSERT_BUTTON_LABEL(nullptr,"dock=center;", "exit", "", 18, SCF(onButtonExit))
    SC_END_PARENT
SC_END_PARENT
```

The result of above code running.  
![](https://github.com/kevinwu1024/SpeedCC-Doc/blob/master/images/image0.png?raw=true)

### Setup Logic in Hierarchy

Building up game logic for easy understanding, so that it can easy to maintain and change.
  
```c++
SC_BEGIN_FSM_LITE(nullptr)
    ON_MSG_BEHAVIOR(kMsgReady, ptrBehaviorReady)
    ON_MSG_BEHAVIOR(kMsgGameOver, ptrBehaviorGameOver)
SC_END_ROLE
```

### Message Driven
SpeedCC based on message to drive features, behaviors and strategies running, such as touch, scnen switch and etc.
Every message listener has chances to handle every message so that decoupling is easy.

### FSM
**Stage** pattern is an **Entity Component System** mixes **Finite State Machine** pattern in SpeedCC.

```c++
SC_BEGIN_FSM(nullptr,kStateID1,MyState)
    AT_STATE(kStateID2)
        ON_MSG_NEXT_STRATEGY(kTestMsgIDNextStrategy, kStateID3)
        ON_MSG_BEHAVIOR(kTestMsgIDLog,ptrBvrLog)
    ENDAT_STATE

    AT_STATE(kStateID3)
        ON_MSG_NEXT_STRATEGY(kTestMsgIDNextStrategy, kStateID1)
        ON_MSG_BEHAVIOR(kTestMsgIDLog,ptrBvrLog)
    ENDAT_STATE

    ON_MSG_NEXT_STRATEGY(kTestMsgIDNextStrategy, kStateID2)
SC_END_ROLE
```

### Scene Navigation
Navigating scene is very easy with SpeedCC, whatever scene it goes to, only to call `back()` then it will back to previous scene with appropriate method automatically.

```c++

// in MyScene1
SCSceneNav()->gotoScene<MyScene2>(kSceneReplace); // goto MyScene2
....

// in MyScene2
SCSceneNav()->back(); // back to MyScene1 automatically

```

### Data Binding
Binding data to scene UI, **User Default** and behavior is one of the key feature in SpeedCC, developer can very easy and quick to connect UI, **User Default** to logic bi-directionally with **Data Binding**.

```c++
auto ptrWatchText = SCWatchString::create();
...
SC_INSERT_LABEL(nullptr,"",ptrWatchText,"",20)
...
(*ptrWatchText) = "abc"; // the label text in screen will be changed to "abc" automatically

```

### Resolution Adapter
SpeedCC can adapter screen resolution with different resolution of assets automcatically, developer even no need to write any code for it, SpeedCC finishs adapter sliently.

### Built-In and Simplified IAP 
SpeedCC wraps **Consumable** and **Non-Consumable** IAP features for iOS and Android, and very easy connecting to game logic.

### High Performance
High effeciency memory management, such as **memeory pool**, **smart pointer**, **lazy loading** and **copy on write** are applied in this framework. 

---

SpeedCC licensed under [MIT](http://opensource.org/licenses/MIT).

Download latest release from [here](https://github.com/kevinwu1024/SpeedCC/releases)

More datails in [documentation](https://github.com/kevinwu1024/SpeedCC-Doc).

More usages in **UI Test Cases** of project and [Sample Games](https://github.com/kevinwu1024/SampleGames).





