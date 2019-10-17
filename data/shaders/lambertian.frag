#version 330

out vec4 bufferColor;


uniform float specularDegree;
uniform vec4 ambientColor;
uniform vec4 diffuseColor;
uniform vec4 specularColor;

in vec4 lightVec;
in vec4 normal;
in vec4 normalView;
in vec4 eyeView;
in vec4 vertex;


vec4 phong(vec3 l, vec3 n, vec3 e) {
	float d = max(dot(-l,n),0.);
	float s = pow(max(dot(reflect(l,n),e),0.),specularDegree);

	vec4 renderedColor;
	renderedColor = ambientColor + diffuseColor*d + specularColor*s;
	return renderedColor;
}


void main(){

	vec3 light = normalize(lightVec.xyz);
	if(light != vec3(0,0,0)){
		// normal, view and light directions (in camera space)
		vec3 n = normalize(normalView.xyz);
		vec3 e = normalize(eyeView.xyz);
		vec3 l = light;


		bufferColor = phong(l, n, e);
	} else {
		bufferColor = diffuseColor;
	}
}
