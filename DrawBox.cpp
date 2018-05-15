void drawCube() {

	GLfloat vertices[] = { 
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
	};          // 8 of vertex coords
	// normal array
	GLfloat normals[] = { 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,   // v0,v1,v2,v3 (front)
		1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,   // v0,v3,v4,v5 (right)
		0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,   // v0,v5,v6,v1 (top)
		-1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0,   // v1,v6,v7,v2 (left)
		0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0,   // v7,v4,v3,v2 (bottom)
		0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1 }; // v4,v7,v6,v5 (back)

	// color array
	GLfloat colors[] = { 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1,   // v0,v1,v2,v3 (front)
		1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1,   // v0,v3,v4,v5 (right)
		1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0,   // v0,v5,v6,v1 (top)
		1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0,   // v1,v6,v7,v2 (left)
		0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0,   // v7,v4,v3,v2 (bottom)
		0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1 }; // v4,v7,v6,v5 (back)

	GLubyte indices[] = { 
		0, 1, 2, 2, 3, 0,   // 36 of indices
		0, 3, 4, 4, 5, 0,
		0, 5, 6, 6, 1, 0,
		1, 6, 7, 7, 2, 1,
		7, 4, 3, 3, 2, 7,
		4, 7, 6, 6, 5, 4 };

	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glPushMatrix();
	glTranslatef(-2, -2, 0);                // move to bottom-left corner

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

}

