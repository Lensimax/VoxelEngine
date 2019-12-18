#include <imgui.h>

#include "meshIndexed.h"

#include <objLoader.h>

MeshIndexed::MeshIndexed(std::string filename) : m_filename(filename){

    setName("Mesh Indexed");

    createMeshFromFile(m_filename);
}


MeshIndexed::~MeshIndexed(){

}


void MeshIndexed::createVAO(){
    const int nbBuffer = 5;

    m_buffers = new GLuint[nbBuffer];

    glGenBuffers(nbBuffer, m_buffers);
    glGenVertexArrays(1,&m_vertexArrayID);

    // create the VBO associated with the grid (the terrain)
    glBindVertexArray(m_vertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER,m_buffers[0]); // vertices
    glBufferData(GL_ARRAY_BUFFER,getNBVertices()*3*sizeof(float),getVertices(),GL_STATIC_DRAW);
    glEnableVertexAttribArray(POSITION_ATTRIB);
    glVertexAttribPointer(POSITION_ATTRIB,3,GL_FLOAT,GL_FALSE,0,(void *)0);

    // m_normals
    glEnableVertexAttribArray(VERTEX_NORMAL_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, getNBVertices()*3* sizeof(float), getNormals(), GL_STATIC_DRAW); //m_normals is std::vector<float>
    glVertexAttribPointer(VERTEX_NORMAL_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // texture coordinates
    glEnableVertexAttribArray(VERTEX_UV_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[2]);
    glBufferData(GL_ARRAY_BUFFER, getNBVertices()*2* sizeof(float), getUVs(), GL_STATIC_DRAW); //m_normals is std::vector<float>
    glVertexAttribPointer(VERTEX_UV_ATTRIB, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // m_colors
    glEnableVertexAttribArray(VERTEX_COLOR_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, m_buffers[3]);
    glBufferData(GL_ARRAY_BUFFER, getNBVertices()*3* sizeof(float), getColors(), GL_STATIC_DRAW); //m_normals is std::vector<float>
    glVertexAttribPointer(VERTEX_COLOR_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, 0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_buffers[4]); // indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_indices.size()*3*sizeof(unsigned int),&m_indices[0],GL_STATIC_DRAW);


    glBindVertexArray(0);
}

void MeshIndexed::drawVAO(){
    glBindVertexArray(m_vertexArrayID);
    glDrawElements(GL_TRIANGLES,3*getNBFaces(),GL_UNSIGNED_INT,(void *)0);
    glBindVertexArray(0);
}

void MeshIndexed::deleteVAO(){
    glDeleteBuffers(5,m_buffers);
    glDeleteVertexArrays(1,&m_vertexArrayID);
    delete m_buffers;
}

void MeshIndexed::createUI(){
    ImGui::Text("Number of vertices : %u", getNBVertices());
    ImGui::Text("Number of faces : %u", getNBFaces());
}


void MeshIndexed::recreate(){
    deleteVAO();
    createMeshFromFile(m_filename);
    createVAO();
}




void MeshIndexed::clear(){
     m_vertices.clear();
     m_normals.clear();
     m_colors.clear();
     
     m_coords.clear();

     m_tangents.clear();
     m_backupVertices.clear();
     m_indices.clear();
}


unsigned int MeshIndexed::getNBFaces() {
    return m_indices.size()/3;
}

void MeshIndexed::createMeshFromFile(std::string filename){

    objl::Loader Loader;

	// Load .obj File
	bool loadout = Loader.LoadFile(filename);

    if(loadout){ // load done

        assert(Loader.LoadedMeshes.size() > 0);

        m_indices = std::vector<unsigned int>(Loader.LoadedMeshes[0].Indices);
        //m_vertices 
        m_vertices.resize(Loader.LoadedMeshes[0].Vertices.size());
        m_normals.resize(m_vertices.size());
        m_coords.resize(m_vertices.size());
        m_tangents.resize(m_vertices.size());
        m_colors.resize(m_vertices.size());



        for(unsigned int i=0; i<Loader.LoadedMeshes[0].Vertices.size(); i++){
            m_vertices[i] = Loader.LoadedMeshes[0].Vertices[i].Position.toGLM();
            m_normals[i] = Loader.LoadedMeshes[0].Vertices[i].Normal.toGLM();
            m_coords[i] = Loader.LoadedMeshes[0].Vertices[i].TextureCoordinate.toGLM();
            m_tangents[i] = glm::vec3(0,1,0);
            m_colors[i] = glm::vec3(1,0,0);
        }

        m_backupVertices = m_vertices;

    } else {
        std::cerr << "Error loading filename : " << filename << "\n";
        exit(1);
    }

}