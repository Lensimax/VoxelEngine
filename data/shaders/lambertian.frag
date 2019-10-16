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





vec4 phong(vec3 l, vec3 n, vec3 e) {


	float d = max(dot(n,l),0.);
	float s = pow(max(dot(reflect(l,n),e),0.),specularDegree);

	vec4 renderedColor;


	renderedColor.xyzw = ambientColor + diffuseColor*d + specularColor*s;
	renderedColor.w = 1;

	return renderedColor;
}

vec4 testPhong(vec4 l, vec4 n, vec4 e) {
	float d = max(dot(n,l),0.);
	float s = pow(max(dot(reflect(l,n),e),0.),specularDegree);

	vec4 renderedColor;

	renderedColor.xyzw = ambientColor + diffuseColor*d + specularColor*s;

	// renderedColor.xyzw = specularColor*s;
	// renderedColor.xyzw = diffuseColor*d;
	renderedColor.w = 1;

	// renderedColor = vec4(0, max(dot(reflect(l,n),e),0.), 0, 1);
	// renderedColor = vec4(0, dot(l,n), 0, 1);

	return renderedColor;
}



void main(){


	if(lightVec != vec4(0.0,0.0,0.0,1.0)){

		// normal, view and light directions (in camera space)
		vec4 n = normalize(normalView);
		vec4 e = normalize(eyeView);
		vec4 l = normalize(lightVec);


		// bufferColor = color;
		// bufferColor = phong(l.xyz, n.xyz, e.xyz);
		bufferColor = testPhong(l, n, e);
		bufferColor = vec4(dot(n,e),0,0,1);
		bufferColor = n;
		bufferColor = vec4(max(dot(reflect(l,n),e),0.),0,0,1);
		bufferColor.a = 1;
		// bufferColor = vec4(n.xyz, 1);
		// bufferColor = testBlinn(color, specularDegree, l.xyz, n.xyz, e.xyz);
	} else {
		bufferColor = diffuseColor;
	}
}
