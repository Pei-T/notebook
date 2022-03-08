```puml
@startmindmap SystemState
* StateControl
    ** Header
        *** **uint32** seq
        *** **uint32** ts_high
        *** **uint32** ts_low
    ** **enum** StateType
        *** kInitializing = 0 // Function initing
        *** kPilotStanby = 1 //Only pilot is allowed to activate
        *** kPilotFunctionActive = 2 // Pilot Has been activated
        *** kApaStanby = 3 // Only Apa is allowed to activate
        *** kHpaStanby = 4 // Only Hpa is allowed to activate
        *** kParkingFunctionActive = 5 // Parking Has been activated
        *** kAebActive = 6 // Aeb has been activeted
        *** kFunctionDisable = 7 // Disable pilot and Parking functions to request activation
    ** StateCtrlParam
        *** **bool** scence_valid = 1
        *** **enum** ScenceInfo state_detail = 2
            **** kNotWork= 0;
            **** kPilotNoa= 1;
            **** kPilotTja= 2;
            **** kPilotAcc= 3;
            **** kPilotAeb= 4;
            **** kPilotLka= 5;
            **** kParkingHpa= 10;
            **** kParkingApa= 11;
            **** kUnknowState= 99;
        *** **bool** scence_valid = 3
        *** ScenceInfo scence_info = 4
            **** **enum** ScenceType
                ***** kUnknowScence= 0
                ***** kHighWay= 1
                ***** kRingRoad= 2
                ***** kUrban= 3
                ***** kGroundParkinglot= 4
                ***** kUndergroudParkinglot= 5
            **** **enum** MapType
                ***** kUnknowMap= 0
                ***** kHdMap= 1
                ***** kSdMap= 2
                ***** kParkingMapAvp= 3
                ***** kParkingMapHvp= 4
                ***** kNoMap= 5
            **** **uint32** scence_data
@endmindmap
```enduml

```puml
@startmindmap SystemState
* **enum** SystemState
        ** kSystemOff= 0
        ** kSystemIniting= 1
        ** kSystemActive= 2
        ** kSystemTerminal= 3
        ** kSystemOta= 4
        ** kSystemFault= 5
@endmindmap
```enduml

```puml
@startmindmap StateReport
* StateReport
    ** Header
        *** **uint32** seq
        *** **uint32** ts_high
        *** **uint32** ts_low
    ** **enum** RequestType
        *** kReqNoResquest= 0
        *** kReqActiveFunction= 1
        *** kReqUnknow= 99
    ** StateRptParam
        *** **bool** state_detail_valid
        *** **enum** StateDetailType
            **** kNotWork= 0
            **** kPilotNoa= 1
            **** kPilotTja= 2
            **** kPilotAcc= 3
            **** kPilotAeb= 4
            **** kPilotLka= 5
            **** kParkingHpa= 10
            **** kParkingApa= 11
            **** kUnknowState= 99
        *** **bool** scence_valid
        *** ScenceInfo
            **** **enum** ScenceType
                ***** kUnknowScence= 0
                ***** kHighWay= 1
                ***** kRingRoad= 2
                ***** kUrban= 3
                ***** kGroundParkinglot= 4
                ***** kUndergroudParkinglot= 5
            **** **enum** MapType
                ***** kUnknowMap= 0
                ***** kHdMap= 1
                ***** kSdMap= 2
                ***** kParkingMapAvp= 3
                ***** kParkingMapHvp= 4
                ***** kNoMap= 5
            **** **uint32** scence_data
@endmindmap
```enduml
