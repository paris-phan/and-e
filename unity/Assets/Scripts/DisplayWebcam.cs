using UnityEngine;

public class DisplayWebcam : MonoBehaviour
{
    private Texture2D Convert_WebCamTexture_To_Texture2d(WebCamTexture _webCamTexture)
    {
        Texture2D _texture2D = new Texture2D(_webCamTexture.width, _webCamTexture.height);
        _texture2D.SetPixels32(_webCamTexture.GetPixels32());

        return _texture2D;
    }

    private WebCamTexture tex;
    private Renderer rend;
    
    void Start ()
    {

        Renderer rend = this.GetComponentInChildren<Renderer>();
        if (rend != null)
        {
            tex = new WebCamTexture(1920,1080,60);
            // Texture2D green = new Texture2D(1920, 1080);
            // for (int y = 0; y < green.height; y++)
            // {
            //     for (int x = 0; x < green.width; x++)
            //     {
            //         green.SetPixel(x, y, Color.green);
            //     }
            // }
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
    }
}
