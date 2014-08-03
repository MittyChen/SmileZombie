#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main(void)
{
	vec4 c = texture2D(CC_Texture0, v_texCoord);
	if(c.w>0)
	{
		gl_FragColor.xyz = vec3(0.5,0.5,0.5);
	}
	
	gl_FragColor.w = c.w;
}