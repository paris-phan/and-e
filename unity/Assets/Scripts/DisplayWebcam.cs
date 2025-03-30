using UnityEngine;

public class DisplayWebcam : MonoBehaviour
{

    public RenderTexture renderTexture;
    private WebCamTexture tex;
    
    private Renderer rend;
    
    void Start ()
    {

        Renderer rend = this.GetComponentInChildren<Renderer>();
        if (rend != null)
        {
            tex = new WebCamTexture(1920,1080,60);
            rend.material.mainTexture = tex;
            
            tex.Play();
        }
        else
        {
            Debug.LogError("RawImage not set");
        }
    }
    
    void Update ()
    {
        // when the webcam feed is updated, update the render texture
        if (tex && tex.didUpdateThisFrame)
        {
            Graphics.Blit(tex, renderTexture);
        }
    }
}
