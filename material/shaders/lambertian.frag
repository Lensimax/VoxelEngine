#version 330

out vec4 bufferColor;


uniform vec4 color;
uniform vec3 light;

uniform vec3 ambientColor;
uniform vec3 specularColor;
uniform float specularDegree;


in vec3 normal;
in vec3 normalView;
in vec3 eyeView;


vec4 phong(vec3 myColor, float specDeg, vec3 aColor, vec3 specColor, vec3 n, vec3 e, vec3 l){


	// diffuse and specular components of the phong shading model
	float diff = max(dot(l,n),0.0);
	float spec = pow(max(dot(reflect(l,n),e),0.0),specDeg);

	// final color
	vec3 color = aColor + diff*myColor + spec*specColor;
	return vec4(color,1.0);
}


void main(){


	if(light != vec3(0.0,0.0,0.0)){

		// normal / view and light directions (in camera space)
		vec3 n = normalize(normalView);
		vec3 e = normalize(eyeView);
		vec3 l = normalize(light);


		// bufferColor = color;
		bufferColor = phong(color.rgb, specularDegree, ambientColor, specularColor, n, e, l);
	} else {
		bufferColor = color;
	}
}
