
## 1 Clibration 流程
```puml
@startuml "statelfow"
!include /home/tangpei/sysmgr/UML/style/core.puml
autonumber
Adas->Sysmgr:Registe
hnote over Sysmgr:Normal
Sysmgr->MCU:Sned State Normal

group Clibration
MCU->MCU:Check Sysmgr state
MCU->Sysmgr:Request Normal
Sysmgr->Adas:Send Request to Adas
Adas->Sysmgr:Calibration confirm
hnote over Sysmgr:Calibration
Sysmgr->MCU:Send State Clibration
Adas->Adas:Do Calibration
Adas->Sysmgr:Send Calibration Result
hnote over Sysmgr:Calibration_Finish
Sysmgr->MCU:Send State Calibration_Finish\nwith Restult
end
Adas->Adas:Restart
Adas->Sysmgr:Registe
hnote over Sysmgr:Normal
Sysmgr->MCU:Sned State Normal
@enduml
```

1. J3上电，状态机进入init状态。ADAS启动并向状态机发送注册。
2. 状态机进入Normal状态，并发送Normal状态给MCU。
3. MCU接收到UDS进入标定命令，然后检查J3状态，若J3未处于normal，则条件不满足。
4. 若J3处于normal，发送状态切换报文请求进入标定状态
5. 通知APP开始标定
6. APP回复确认标定
7. SysMgr将系统状态从Normal切换为Camera_Onl_Calibration，SysMgr再将状态（eg:Camera_Onl_Calibration）回复给MCU,MCU可根据一定时间内是否收到状态切换报文来判断请求标定的消息是否正确送达。
8. 标定期间，仍然保持心跳通信，state对应为标定状态。
9. ADAS标定结束后将结果发送给SysMgr，同时通知SysMgr将系统状态从Camera_Onl_Calibration切换至Camera_Onl_Calibration_finish，
10. SysMgr会把状态切换到Camera_Onl_Calibration_finish状态,SysMgr会把Camera_. Onl_Calibration_finish状态以及标定结果发给MCU；. MCU接收SOC发送的标定结果报文，判断标定结果；若一定时间内MCU未收到标定结果，则认为标定超时。
11. ADAS标定完成后重启
12. ADAS重启回到normal状态，重新注册，SysMgr切换到Normal。


## 2 OTA 流程
```puml
@startuml "statelfow"
!include /home/tangpei/sysmgr/UML/style/core.puml
autonumber
participant APPs order 10
participant Sysmgr order 20
participant OtaService order 30
...
hnote over Sysmgr:Normal
group OTA
OtaService->Sysmgr:Request to OTA
hnote over Sysmgr:OTA_PREPARE
Sysmgr->Sysmgr:Start 5s timer
group Not Timeover
Sysmgr->APPs:Request to OTA,Call Ota_callback.
APPs->Sysmgr:Ota confirm
hnote over Sysmgr:OTA
Sysmgr->OtaService:confirm OTA state call the DO_OTA callbace
OtaService->OtaService: Do OTA
end
group Timeover 5s

hnote over Sysmgr:OTA
Sysmgr->OtaService:confirm OTA state call the DO_OTA callbace
OtaService->OtaService: Do OTA
end
end
== Reboot ==
@enduml
```
0. 所有App包括OTAService调用状态机注册接口后，状态机进入**NORMAL**。
0. OtaService向状态机请求进入OTA。状态机在NORMAL状态收到请求，立即进入**OTA_PREPARE**状态
0. 状态机在进入**OTA_PREPARE**后，会开启一个5s的计时器。
0. 状态机向所有的APPs发送进入OTA请求，调用其Ota_callback回调
0. 所有APPs在准备好后，回复状态机confirm，状态机进入**OTA**状态。
0. 状态机向OtaServce确认OTA状态
0. OtaService及其相关进程进行OTA工作。

## 下电流程
```puml
@startuml "statelfow"
!include /home/tangpei/sysmgr/UML/style/core.puml
autonumber
!pragma teoz true
participant MCU order 40
participant Sysmgr order 30
participant APPs order 10
...
hnote over Sysmgr:SOME_STATE
group Shutdown
{start} MCU->Sysmgr:Request power_off
activate Sysmgr
Sysmgr->Sysmgr:5s Timer
hnote over Sysmgr:AFTERRUN
Sysmgr->APPs:Request to SHUTDOWN,Call SHUTDOWN_callback.
activate APPs
deactivate Sysmgr
APPs->>APPs:Prepare Shutdown
group #LightBlue Not Timeover 
APPs->Sysmgr:shutdown confirm
activate Sysmgr
deactivate APPs
hnote over Sysmgr:SHUTDOWN
{end} Sysmgr->MCU:power_off confirm
deactivate Sysmgr
else #pink Timeover 5s
hnote over Sysmgr:SHUTDOWN
Sysmgr->MCU:shutdown confirm
end

==Power Off==

@enduml
{start} <-> {end} :Max 5s
```
1. 在**NORMAL**，**INIT**，**SYS_FAYLT**状态下，MCU向状态机请求下电。
2. 状态机接收到请求后，立即进入AFTERRUN状态，并开启一个5s计时器。
3. 状态机向APPs发送下电请求，并调用**shutdown_callback**
4. 各APP完成下电工作后，向状态机确认下电。
5. 状态机在收到所有下电确认后，切换到**SHUTDOWN**状态，并向MUC确认下电。
6. 在超时情况下，状态机开启的5s计时器会强行将状态切换到**SHUTDOWN**状态。并向MCU确认下电。
