using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using WebSocketSharp;
using UnityEngine.XR.Hands;
using UnityEngine.XR;

public class XRHandToRoArmController : MonoBehaviour
{
    /* Enums for the hand type and the hand configuration */

    //make sure to change the hand type in the inspector
    public enum HandType
    {
        Left,
        Right
    }

    /* WebSocket Configuration */
    public HandType handType;
    public XRHand xrHand;
    public Vector3 handPos;

    /* WebSocket Configuration */
    private WebSocket ws;
    private float posUpdateTimer = 0f;
    private float posUpdateInterval = 0.1f;

    /* Gripper Configuration */
    private float pinchThreshold = 0.1f; //change this to the minimum pinch strength to detect pinch stregnth
    private bool isPinching = false;
    private float angleOfPinch;
    private float converted_angleOfPinch; //because 0-1 in the meta quest is not the same as 0-1 in the roarm , theyare flipped

    /* Reference to the camera transform (headset) */
    private Transform centerEyeAnchor;
    
    /* XR Hands references */
    private XRHandSubsystem handSubsystem;
    private XRHandJoint thumbTip;
    private XRHandJoint indexTip;
    private XRHandJoint middleTip;
    private XRHandJoint ringTip;
    private XRHandJoint pinkyTip;

    private float left_x_offset = .14f;
    private float right_x_offset = -.11f;
    private float y_offset = .35f;
    private float z_offset = -.14f;

    // JSON class for sending hand position to the server
    [Serializable]
    public class HandPosition
    {
        public int T = 1041;
        public float x;
        public float y;
        public float z;
        public float t;
        public string handType; // Added to identify which hand sent the data
    }




    void Start()
    {
        // Get the main camera (center eye)
        centerEyeAnchor = Camera.main.transform;
        
        // Get XR Hand subsystem
        List<XRHandSubsystem> handSubsystems = new List<XRHandSubsystem>();
        SubsystemManager.GetSubsystems(handSubsystems);
        if (handSubsystems.Count > 0)
        {
            handSubsystem = handSubsystems[0];
        }
        else
        {
            Debug.LogError("No XR Hand subsystem found!");
        }
    }

    void OnEnable()
    {
        // Initialize WebSocket connection when enabled
        ws = new WebSocket("ws://127.0.0.1:8766");
        ws.Connect();

        ws.OnOpen += (sender, e) => {
            Debug.Log($"WebSocket connected for {handType} hand");
        };

        ws.OnClose += (sender, e) => {
            Debug.Log($"WebSocket closed for {handType} hand");
        };

        ws.OnError += (sender, e) => {
            Debug.Log($"WebSocket error for {handType} hand: {e.Message}");
        };
    }

    /* Logic for gripping */
    void pinchObject(){
        if (handSubsystem == null || !handSubsystem.running) 
            return;
            
        XRHand hand = (handType == HandType.Left) ? 
            handSubsystem.leftHand : handSubsystem.rightHand;
            
        if (!hand.isTracked)
            return;
            
        // Get finger joints
        if (!GetFingerTips(hand))
            return;
            
        // Calculate pinch strength by measuring distance between thumb and index finger
        float thumbToIndexDist = Vector3.Distance(GetJointPosition(thumbTip), GetJointPosition(indexTip));
        float thumbToMiddleDist = Vector3.Distance(GetJointPosition(thumbTip), GetJointPosition(middleTip));
        float thumbToRingDist = Vector3.Distance(GetJointPosition(thumbTip), GetJointPosition(ringTip));
        float thumbToPinkyDist = Vector3.Distance(GetJointPosition(thumbTip), GetJointPosition(pinkyTip));
        
        // Normalize distance (smaller distance = stronger pinch)
        float maxDistance = 0.1f; // Adjust based on real-world hand size
        float pinchStrength = 1 - Mathf.Clamp01(thumbToIndexDist / maxDistance);
        
        // Update angle continuously
        converted_angleOfPinch = 1 - pinchStrength;
        angleOfPinch = converted_angleOfPinch * (Mathf.PI / 2f);
        
        // 1 means closer to pinched
        // 0 means not pinching at all
        bool isPinchingNow = pinchStrength >= pinchThreshold;

        // Only update if the pinch state has changed
        if (isPinchingNow != isPinching)
        {
            isPinching = isPinchingNow;
            if (isPinching)
            {
                Debug.Log($"{handType} hand: Pinching");
            }
            else
            {
                Debug.Log($"{handType} hand: Released pinch");
            }
        }
    }
    
    private bool GetFingerTips(XRHand hand)
    {
        // Get finger tip joints
        bool found = true;
        found &= hand.GetJoint(XRHandJointID.ThumbTip).TryGetPose(out var thumbPose);
        found &= hand.GetJoint(XRHandJointID.IndexTip).TryGetPose(out var indexPose);
        found &= hand.GetJoint(XRHandJointID.MiddleTip).TryGetPose(out var middlePose);
        found &= hand.GetJoint(XRHandJointID.RingTip).TryGetPose(out var ringPose);
        found &= hand.GetJoint(XRHandJointID.LittleTip).TryGetPose(out var pinkyPose);
        
        if (found)
        {
            thumbTip = hand.GetJoint(XRHandJointID.ThumbTip);
            indexTip = hand.GetJoint(XRHandJointID.IndexTip);
            middleTip = hand.GetJoint(XRHandJointID.MiddleTip);
            ringTip = hand.GetJoint(XRHandJointID.RingTip);
            pinkyTip = hand.GetJoint(XRHandJointID.LittleTip);
        }
        
        return found;
    }
    
    private Vector3 GetJointPosition(XRHandJoint joint)
    {
        if (joint.TryGetPose(out Pose pose))
        {
            return pose.position;
        }
        return Vector3.zero;
    }

    /* method that updates every frame*/
    void Update()
    {
        if (handSubsystem != null && handSubsystem.running)
        {
            XRHand hand = (handType == HandType.Left) ? 
                handSubsystem.leftHand : handSubsystem.rightHand;
                
            if (hand.isTracked && centerEyeAnchor != null)
            {
                posUpdateTimer += Time.deltaTime;

                if (posUpdateTimer >= posUpdateInterval)
                {
                    posUpdateTimer = 0f;

                    // Get hand root position
                    XRHandJoint palmJoint = hand.GetJoint(XRHandJointID.Palm);
                    if (palmJoint.TryGetPose(out Pose palmPose))
                    {
                        Vector3 worldHandPos = palmPose.position;
                        handPos = centerEyeAnchor.InverseTransformPoint(worldHandPos);
                        
                        //seeing if the hand is pinching 
                        pinchObject();
                        
                        HandPosition myHandPosition = new HandPosition
                        {
                            x = handPos.x + (handType == HandType.Left ? left_x_offset : right_x_offset),
                            y = handPos.y + y_offset,
                            z = handPos.z + z_offset,
                            t = angleOfPinch,
                            handType = handType.ToString()
                        };

                        string json_handPos = JsonUtility.ToJson(myHandPosition);
                        Debug.Log($"JSON for {handType} hand: {json_handPos}");

                        if (!string.IsNullOrEmpty(json_handPos) && ws != null && ws.IsAlive)
                        {
                            ws.Send(json_handPos);
                        }
                    }
                }
            }
        }
    }

    void OnDestroy()
    {
        if (ws != null && ws.IsAlive)
        {
            ws.Close();
        }
    }

    void OnDisable()
    {
        // Close WebSocket connection when component is disabled
        if (ws != null && ws.IsAlive)
        {
            ws.Close();
            ws = null;
        }
    }
}