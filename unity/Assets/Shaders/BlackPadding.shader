Shader "Unlit/BlackPadding"
{
    Properties
    {
        _MainTex ("Webcam Texture", 2D) = "white" {}
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag

            #include "UnityCG.cginc"

            struct appdata_t
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct v2f
            {
                float2 uv : TEXCOORD0;
                float4 vertex : SV_POSITION;
            };

            sampler2D _MainTex;
            float4 _MainTex_ST;

            v2f vert (appdata_t v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = TRANSFORM_TEX(v.uv, _MainTex);
                return o;
            }

            fixed4 frag (v2f i) : SV_Target
            {
                // Define the aspect ratio of the webcam feed
                float2 aspect = float2(1920.0 / 3840.0, 1080.0 / 3840.0);
                float2 centeredUV = (i.uv - 0.5) / aspect + 0.5;

                // Check if the UV coordinates are inside the valid area
                if (centeredUV.x < 0 || centeredUV.x > 1 || centeredUV.y < 0 || centeredUV.y > 1)
                {
                    return fixed4(0, 0, 0, 1); // Black outside the region
                }

                return tex2D(_MainTex, centeredUV);
            }
            ENDCG
        }
    }
}