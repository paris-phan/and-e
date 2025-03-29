using UnityEngine;
using UnityEngine.Video;

public class DisplayVideo : MonoBehaviour
{


    private WebCamTexture tex;
    private Renderer rend;
    private RenderTexture rt;
    
    void Start ()
    {
        // get the render texture output from the video player component
        rt = GetComponent<VideoPlayer>().targetTexture;
        if (rt == null)
        {
            Debug.LogError("Render texture not set");
            return;
        }
        Renderer rend = this.GetComponentInChildren<Renderer>();
        if (rend != null)
        {
            // set the render texture as the main texture of the material
            rend.material.mainTexture = rt;
        }
        else
        {
            Debug.LogError("RawImage not set");
        }
    }
    
    void Update ()
    {
    }
}