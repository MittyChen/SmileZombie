/*
 * provide fliter cocos2dx 3.0
 * Copyright (c) 2014.06
 * Author yl
 */

"                                \n\
#ifdef GL_ES                     \n\
precision mediumpfloat;         \n\
#endif                           \n\
                                 \n\
varying vec4 v_fragmentColor;    \n\
varying vec2 v_texCoord;         \n\
uniform sampler2D CC_Texture0;   \n\
                                 \n\
uniformfloat Hue;               \n\
uniformfloat Sat;               \n\
uniformfloat Lig;               \n\
uniformfloat Bri;               \n\
uniform vec2 TextureSize;        \n\
uniform vec3 GlowColor;          \n\
uniformfloat GlowRange;         \n\
uniformfloat GlowExpand;        \n\
uniform vec3 OutlineColor;       \n\
uniformfloat OutlineRange;      \n\
                                                                     \n\
float Hue_2_RGB(float v1,float v2, float vH )                       \n\
{                                                                    \n\
   float ret;                                                       \n\
   if ( vH < 0.0 )                                                  \n\
        vH +=1.0;                                                   \n\
   if ( vH > 1.0 )                                                  \n\
        vH -=1.0;                                                   \n\
   if ( ( 6.0 * vH ) <1.0 )                                        \n\
        ret = ( v1 + ( v2 - v1 ) *6.0 * vH );                       \n\
   else if ( (2.0 * vH ) < 1.0 )                                   \n\
        ret = ( v2 );                                                \n\
   else if ( (3.0 * vH ) < 2.0 )                                   \n\
        ret = ( v1 + ( v2 - v1 ) * ( (2.0 / 3.0 ) - vH ) *6.0 );   \n\
   else                                                             \n\
        ret = v1;                                                    \n\
   return ret;                                                      \n\
}                                                                    \n\
                                                                     \n\
void main(void)                                                      \n\
{                                                                    \n\
    vec4 color = texture2D(CC_Texture0, v_texCoord);                 \n\
   float R, G, B, A;                                                \n\
    R = color.r;                                                     \n\
    G = color.g;                                                     \n\
    B = color.b;                                                     \n\
    A = color.a;                                                     \n\
                                                                     \n\
   if( A != 0.0 )                                   \n\
    {                                                \n\
       if( Hue != 0.0 || Sat !=0.0 || Lig != 0.0 ) \n\
        {                                            \n\
           float Cmax, Cmin;                        \n\
           float D;                                 \n\
           float H, S, L;                           \n\
                                                     \n\
            Cmax = max (R, max (G, B));              \n\
            Cmin = min (R, min (G, B));              \n\
            L = (Cmax + Cmin) /2.0;                 \n\
                                                     \n\
           if (Cmax == Cmin)                        \n\
            {                                        \n\
                H =0.0;                             \n\
                S =0.0;                             \n\
            }                                        \n\
           else                                     \n\
            {                                        \n\
                D = Cmax - Cmin;                     \n\
               if (L < 0.5)                         \n\
                {                                    \n\
                    S = D / (Cmax + Cmin);           \n\
                }                                    \n\
               else                                 \n\
                {                                    \n\
                    S = D / (2.0 - (Cmax + Cmin));   \n\
                }                                    \n\
                                                     \n\
               if (R == Cmax)                       \n\
                {                                    \n\
                    H = (G - B) / D;                 \n\
                }                                    \n\
               else                                 \n\
                {                                    \n\
                   if (G == Cmax)                   \n\
                    {                                \n\
                        H =2.0 + (B - R) /D;        \n\
                    }                                \n\
                   else                             \n\
                    {                                \n\
                        H =4.0 + (R - G) / D;       \n\
                    }                                \n\
                }                                    \n\
                H = H /6.0;                         \n\
            }                                        \n\
                                                     \n\
            // modify H/S/L values                   \n\
            H += Hue;                                \n\
            S += Sat;                                \n\
            L += Lig;                                \n\
                                                     \n\
           if (H < 0.0)                             \n\
            {                                        \n\
                H = H +1.0;                         \n\
            }                                        \n\
                                                     \n\
            H = clamp(H,0.0, 1.0);                  \n\
            S = clamp(S,0.0, 1.0);                  \n\
            L = clamp(L,0.0, 1.0);                  \n\
                                                     \n\
            // convert back to RGB                   \n\
           float var_2, var_1;                      \n\
                                                     \n\
           if (S == 0.0)                                           \n\
            {                                                       \n\
                R = L;                                              \n\
                G = L;                                              \n\
                B = L;                                              \n\
            }                                                       \n\
           else                                                    \n\
            {                                                       \n\
               if ( L < 0.5 )                                      \n\
                {                                                   \n\
                    var_2 = L * (1.0 + S );                        \n\
                }                                                   \n\
               else                                                \n\
                {                                                   \n\
                    var_2 = ( L + S ) - ( S * L );                  \n\
                }                                                   \n\
                                                                    \n\
                var_1 =2.0 * L - var_2;                            \n\
                                                                    \n\
                R = Hue_2_RGB( var_1, var_2, H + (1.0 / 3.0 ) );   \n\
                G = Hue_2_RGB( var_1, var_2, H );                   \n\
                B = Hue_2_RGB( var_1, var_2, H - (1.0 / 3.0 ) );   \n\
            }                                                       \n\
        }                                                           \n\
                                                                    \n\
                                                                    \n\
       if ( Bri != 0.0 )                                           \n\
        {                                                           \n\
           if ( Bri > 0.0 )                                        \n\
            {                                                       \n\
                R = R + (255.0 - R) /255.0 * Bri;                  \n\
                G = G + (255.0 - G) /255.0 * Bri;                  \n\
                B = B + (255.0 - B) /255.0 * Bri;                  \n\
            }                                                       \n\
           else                                                    \n\
            {                                                       \n\
                R = R + R /255.0 * Bri;                            \n\
                G = G + G /255.0 * Bri;                            \n\
                B = B + B /255.0 * Bri;                            \n\
            }                                                       \n\
        }                                                           \n\
    }                                                               \n\
   else                                                                                                                                \n\
    {                                                                                                                                   \n\
                                                                                                                                        \n\
       if( GlowRange > 0.0 )                                                                                                           \n\
        {                                                                                                                               \n\
           float samplerPre = 2.0;                                                                                                     \n\
           float radiusX = 1.0 / TextureSize.x;                                                                                        \n\
           float radiusY = 1.0 / TextureSize.y;                                                                                        \n\
           float glowAlpha = 0.0;                                                                                                      \n\
           float count = 0.0;                                                                                                          \n\
           for( float i = -GlowRange ; i <= GlowRange ; i += samplerPre )                                                              \n\
            {                                                                                                                           \n\
               for( float j = -GlowRange ; j <= GlowRange ; j += samplerPre )                                                          \n\
                {                                                                                                                       \n\
                    vec2 samplerTexCoord = vec2( v_texCoord.x + j * radiusX , v_texCoord.y + i * radiusY );                             \n\
                   if( samplerTexCoord.x < 0.0 || samplerTexCoord.x > 1.0 || samplerTexCoord.y <0.0 || samplerTexCoord.y > 1.0 )      \n\
                        glowAlpha +=0.0;                                                                                               \n\
                   else                                                                                                                \n\
                        glowAlpha += texture2D( CC_Texture0, samplerTexCoord ).a;                                                       \n\
                    count +=1.0;                                                                                                       \n\
                }                                                                                                                       \n\
            }                                                                                                                           \n\
            glowAlpha /= count;                                                                                                         \n\
            R = GlowColor.r;                                                                                                            \n\
            G = GlowColor.g;                                                                                                            \n\
            B = GlowColor.b;                                                                                                            \n\
            A = glowAlpha * GlowExpand;                                                                                                 \n\
        }                                                                                                                               \n\
                                                                                                                                        \n\
                                                                                                                                        \n\
       if( OutlineRange > 0.0 )                                                                                                        \n\
        {                                                                                                                               \n\
           float radiusX = 1.0 / TextureSize.x;                                                                                        \n\
           float radiusY = 1.0 / TextureSize.y;                                                                                        \n\
           bool outline = false;                                                                                                       \n\
           for( float i = -OutlineRange ; i <= OutlineRange ; i ++ )                                                                   \n\
            {                                                                                                                           \n\
   for( float j = -OutlineRange ; j <= OutlineRange ; j ++ )                                                               \n\
                {                                                                                                                       \n\
                    vec2 samplerTexCoord = vec2( v_texCoord.x + j * radiusX , v_texCoord.y + i * radiusY );                             \n\
                   if( samplerTexCoord.x >= 0.0 && samplerTexCoord.x <= 1.0 && samplerTexCoord.y >=0.0 && samplerTexCoord.y <= 1.0 )  \n\
                    {                                                                                                                   \n\
                       if( texture2D( CC_Texture0, samplerTexCoord ).a >0.0 )                                                         \n\
                        {                                                                                                               \n\
                            outline =true;                                                                                             \n\
                           break;                                                                                                      \n\
                        }                                                                                                               \n\
                    }                                                                                                                   \n\
                }                                                                                                                       \n\
            }                                                                                                                           \n\
           if( outline )                       \n\
            {                                   \n\
                R = OutlineColor.r;             \n\
                G = OutlineColor.g;             \n\
                B = OutlineColor.b;             \n\
                A =255.0;                      \n\
            }                                   \n\
        }                                       \n\
    }                                           \n\
    gl_FragColor = vec4( R , G , B , A );       \n\
}                                               \n\
";