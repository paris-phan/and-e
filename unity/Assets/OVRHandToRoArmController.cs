using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using WebSocketSharp;

public class OVRHandToRoArmController : MonoBehaviour
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
    public OVRHand ovrHand;
    public OVRSkeleton ovrSkeleton;
    public Vector3 handPos;

    /* WebSocket Configuration */
    private WebSocket ws;
    private float posUpdateTimer = 0f;
    private float posUpdateInterval = 0.1f;

    /* Gripper Configuration */
    private float pinchThreshold = 0.7f;
    private bool isPinching = false;
    private float angleOfPinch;

    /* Reference to the camera transform (headset) */
    private Transform centerEyeAnchor;

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
        float pinchStrength = ovrHand.GetFingerPinchStrength(OVRHand.HandFinger.Index);
        bool isPinching = pinchStrength > pinchThreshold;
        if (isPinching != isPinching)
        {
            isPinching = isPinching;
            if (isPinching)
            {
                Debug.Log($"{handType} hand: Gripping");
                angleOfPinch = 0;
            }
            else
            {
                Debug.Log($"{handType} hand: Releasing");
                angleOfPinch = 3.14f;
            }
        }
    }

    /* method that updates every frame*/
    void Update()
    {
        if (ovrHand && ovrHand.IsTracked && centerEyeAnchor != null)
        {
            posUpdateTimer += Time.deltaTime;

            if (posUpdateTimer >= posUpdateInterval)
            {
                posUpdateTimer = 0f;

                // Get hand position relative to the headset (center eye) 
                Vector3 worldHandPos = ovrHand.transform.position;
                handPos = centerEyeAnchor.InverseTransformPoint(worldHandPos);
                
                //seeing if the hand is pinching 
                pinchObject();
                
                HandPosition myHandPosition = new HandPosition
                {
                    x = handPos.x,
                    y = handPos.y,
                    z = handPos.z,
                    t = 3.14f,
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

    void OnDestroy()
    {
        if (ws != null && ws.IsAlive)
        {
            ws.Close();
        }
    }
}
