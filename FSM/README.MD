skinparam backgroundColor #EEEBDC
``` puml


skinparam linetype ortho
class SysContext{
    -input_msg_queue_
    +STMWorker()
    +HandleSignal()
}
package "Communication Module" <<Folder>> {

class Session{
    +RecvInputMsg()
    +SendOutputSignal()
    +SendAck()
}

class OutputHandler{
    +SendOutputSignal()
}

class InputHandler{
    +RecvInputMsg()
}

class APPsProtocolHandler{
    +WrapSignalToMsg()
    +ExtractSignalFromMsg()
}

class IpcInterfaceOut{
    +DoSendJob()
}
class IpcInterfaceIn{
    +DoRecvJob()
}

class ZmqIpcImplOut{
    +DoSendJob()
}
class ZmqIpcImplIn{
    +DoBlockRecvJob()
}
package "AUTOSAR Interface"{
interface In{
    PowerModeMsg()
    TriggerIn()
}
interface Out{
    PowerModeRespMsg()
    TriggerOut()
}
interface InOut{
    TriggerInOut()
}
Session -up-* SysContext
OutputHandler -left-* Session
InputHandler -up-* Session
IpcInterfaceOut -left-* OutputHandler
ZmqIpcImplOut -left-|> IpcInterfaceOut
APPsProtocolHandler -up-o OutputHandler
APPsProtocolHandler -left-o InputHandler
IpcInterfaceIn -up-* InputHandler
ZmqIpcImplIn -left-|> IpcInterfaceIn

In .left.|> ZmqIpcImplIn
Out .up.|> ZmqIpcImplOut
InOut .left.o In
InOut .up.o Out


}
}
```

``` puml
@startuml
skinparam linetype ortho
state FunctionState{
    state Calibration
    State Dota
    state OTA
}
State MachineState{
    State PowerModeOn
    State NormalDriving
    State SysFault
    State PowerModeOff
}
[*] --> PowerModeOn
PowerModeOn --> NormalDriving
NormalDriving --> PowerModeOff
    NormalDriving  -->  OTA
    OTA --> PowerModeOff
    NormalDriving  -->  Calibration
    Calibration --> NormalDriving
    NormalDriving --> Dota
    Dota --> NormalDriving
PowerModeOff --> [*]
NormalDriving --> SysFault
SysFault --> NormalDriving

@enduml
```
callback 能自动确认。
``` puml
@startuml
skinparam linetype ortho
class State{
    -uint32 signal
    -string name
    -string topic
    -function callback
}
class Context{
  map<name,State> state_map
}
class Communication{
    queue<Msg> queue_msg
    PushMsg()
}
State --o Context
Communication --o Context
@enduml
```