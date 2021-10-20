#include <iostream>
#include "Sprite.h"
#include "Scene.h"

Sprite::Sprite()
{
	Image = nullptr;
	Size.x = 0;
	Size.y = 0;
	Position.x = 0;
	Position.y = 0;
	ImageAngle = 0.0;
	LastAngle = ImageAngle;
	Scale = 1.0;
	MoveAngle = 0.0;
	Speed = 0.0;
	Velocity.x = 0;
	Velocity.y = 0;
	Acceleration.x = 0;
	Acceleration.y = 0;
	Scene = nullptr;
	BoundAction = 0;
	bCollisionEnabled = true;
}

void Sprite::SetScale(double s)
{
	Scale = s;
}

void Sprite::VectorProjection(double Speed)
{
	Velocity.x = Speed * cos(MoveAngle) + Acceleration.x;
	Velocity.y = Speed * sin(MoveAngle) + Acceleration.y;
	this->Speed = sqrt((Velocity.x * Velocity.x) + (Velocity.y * Velocity.y));
	MoveAngle = atan2(Velocity.y, Velocity.x);
	//ImageAngle = MoveAngle + M_PI/2;
}

SDL_Texture* Sprite::SetImage(SDL_Renderer* renderer, std::string ImagePath, Vec2D InitPosition)
{
	SDL_Texture* loaded = IMG_LoadTexture(renderer, ImagePath.c_str());
	if (!loaded)
	{
		std::cout << "Unable to find " << ImagePath << ". Check path for correctness." << std::endl;
		std::cout << IMG_GetError() << std::endl;
		return nullptr;
	}
	else
	{
		int w;
		int h;
		Image = loaded;
		SDL_QueryTexture(Image, NULL, NULL, &w, &h);
		texture.x = InitPosition.x;
		texture.y = InitPosition.y;
		Position.x = texture.x;
		Position.y = texture.y;
		texture.w = Scale*w;
		texture.h = Scale*h;
		Center.x = Position.x + (texture.w / 2.00);
		Center.y = Position.y + (texture.h / 2.00);
		D.x = Center.x - texture.x;
		D.y = Center.y - texture.y;
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderDrawPoint(renderer, Center.x, Center.y);
		SDL_RenderDrawPoint(renderer, texture.x, texture.y);
		SetVertices();
		return Image;
	}
}

void Sprite::Draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, Image, NULL, &texture);
	SDL_RenderPresent(renderer);
}

void Sprite::Update(SDL_Renderer* renderer){ return; } //Update, in implemenatation, should only be updating location, rotation, speed etc.
void Sprite::PlayerInput(SDL_Event Event, SDL_Renderer* renderer){ return; }
void Sprite::DefaultBehavior(){ return; }

void Sprite::Hide()
{

}

void Sprite::Show()
{

}

void Sprite::SetSpeed(double Speed)
{
	VectorProjection(Speed);
}

void Sprite::SetImageAngle(double Degrees)
{
	ImageAngle = ConvertToRadians(Degrees);
}

void Sprite::SetMoveAngle(double Degrees)
{
	MoveAngle = ConvertToRadians(Degrees);
}

void Sprite::AddForce(Vec2D Force)
{
	Acceleration.x += Force.x;
	Acceleration.y += Force.y;
}

void Sprite::SetBoundAction()
{

}

void Sprite::CheckBounds()
{
	
}

bool Sprite::CollidesWith(Sprite* OtherSprite)
{
	std::stack<Vec2D> P1Normals = GetNormals();
	std::stack<Vec2D> P2Normals = OtherSprite->GetNormals();
	if(!SeparateAxisTheorem(P1Normals, OtherSprite)){ return false; }
	if(!SeparateAxisTheorem(P2Normals, OtherSprite)){ return false; }
	//if we got through all normals we can prove that there is a collision
	return true;
}

double Sprite::DistanceTo(Sprite* OtherSprite)
{
	double DeltaX = (this->Position.x - OtherSprite->Position.x) * (this->Position.x - OtherSprite->Position.x);
	double DeltaY = (this->Position.y - OtherSprite->Position.y) * (this->Position.y - OtherSprite->Position.y);
	return sqrt(DeltaX + DeltaY);
}

double Sprite::AngleTo(Sprite* OtherSprite)
{
	double dot = Position.DotProduct(OtherSprite->Position);
	double MagA = Position.Magnitude();
	double MagB = OtherSprite->Position.Magnitude();
	double theta = acos(dot / (MagA*MagB));
	return theta;
}

double Sprite::ConvertToRadians(double Degrees)
{
	return Degrees * M_PI / 180.00;
}

double Sprite::ConvertToDegrees(double Radians)
{
	return Radians * 180.00 / M_PI;
}

void Sprite::SetVertices()
{
	Vec2D vert1{(double)texture.x, (double)texture.y};
	Vec2D vert2{(double)texture.x + (double)texture.w, (double)texture.y};
	Vec2D vert3{(double)texture.x, (double)texture.y + (double)texture.h};
	Vec2D vert4{(double)texture.x + (double)texture.w, (double)texture.y + (double)texture.h};
	//Order of insertion of vertices matters
	vertices.push_back(vert1);
	vertices.push_back(vert3);
	vertices.push_back(vert4);
	vertices.push_back(vert2);
}

void Sprite::UpdateVertices()
{
	std::vector<Vec2D> NewVerts;
	Vec2D vert;
	for (int i = vertices.size() - 1; i >= 0; --i)
	{
		vert.x = ((vertices[i].x - Center.x) * cos(ImageAngle - LastAngle)) - ((vertices[i].y - Center.y) * sin(ImageAngle - LastAngle)) + Center.x;
		vert.y = ((vertices[i].x - Center.x) * sin(ImageAngle - LastAngle)) + ((vertices[i].y - Center.y) * cos(ImageAngle - LastAngle)) + Center.y;
		NewVerts.push_back(vert);
	}
	LastAngle = ImageAngle;
	vertices = NewVerts;
}

void Sprite::SetCollisionEnabled(bool Set)
{
	bCollisionEnabled = Set;
}

void Sprite::MoveSprite()
{
	std::vector<Vec2D> NewVerts;
	Vec2D vert;
	Position.x += Velocity.x;
	Position.y += Velocity.y;
	Center.x += Velocity.x;
	Center.y += Velocity.y;
	for (int i = 0; i < vertices.size(); ++i)
	{
		vert.x = vertices[i].x + Velocity.x;
		vert.y = vertices[i].y + Velocity.y;
		NewVerts.push_back(vert);
	}
	//Here I am locking the texture to be relative to the center of the 'collision' box
	//This prevents a bug where the sprite and the collision box separate from each other
	texture.x = Center.x - D.x;
	texture.y = Center.y - D.y;
	vertices = NewVerts;
}

//Returns the normalized normal vectors of an 'edge' (line seg between 2 pts) of a sprite 
std::stack<Vec2D> Sprite::GetNormals()
{
	Vec2D Normal;
	std::stack<Vec2D> Normals;
	for (int i = vertices.size() - 1; i > -1; --i)
	{
		if (i == 0)
		{
			Normal = vertices[0].GetNormal(vertices[vertices.size() - 1]);
			Normal.Normalize();
			Normals.push(Normal);
			break;
		}
		Normal = vertices[i].GetNormal(vertices[i - 1]);
		Normal.Normalize();
		Normals.push(Normal);
	}
	return Normals;
}

/*
Project points to normalized normal, find min and max for both polygons (p1, p2)
Init values first. 
Find scalar offset, then check if there is a gap
If there is a gap, we can move stop checking for collisions, as there is no collision possible
If no gap, continue checking other normals. Must check normals on BOTH polygons
I chose this method because it actually works for ANY CONVEX polygon (square, rect, triangle, can make work with circle, etc.)
Unfortunately due to the way I am currently calculating the vertices, squares are the only collidable shapes
However if I could figure a way to get all vertices of a general shape, then this would work for any convex shape
*/
bool Sprite::SeparateAxisTheorem(std::stack<Vec2D> Normals, Sprite* OtherSprite)
{
	std::vector<Vec2D> P2Verts;
	P2Verts = OtherSprite->vertices;
	while (!Normals.empty())
	{
		double p1min = vertices[0].DotProduct(Normals.top());
		double p1max = p1min;
		double p2min = P2Verts[0].DotProduct(Normals.top());
		double p2max = p2min;
		for (int i = 1; i < vertices.size(); ++i)
		{
			double test = vertices[i].DotProduct(Normals.top());
			p1min = fmin(p1min, test);
			p1max = fmax(p1max, test);
		}
		for (int i = 1; i < P2Verts.size(); ++i)
		{
			double test = P2Verts[i].DotProduct(Normals.top());
			p2min = fmin(p2min, test);
			p2max = fmax(p2max, test);
		}
		/*Vec2D VectorOffset{ Position.x - OtherSprite->Position.x, Position.y - OtherSprite->Position.y };
		double ScalarOffset = VectorOffset.DotProduct(Normals.top());
		p1min += ScalarOffset;
		p1max += ScalarOffset;*/
		if (p1min - p2max > 0 || p2min - p1max > 0)
		{
			return false;
		}
		Normals.pop();
	}
	return true;
}

void Sprite::SetPlayerStatus(bool IsPlayer)
{
	bPlayer = IsPlayer;
}

Vec2D Sprite::GetPosition()
{
	return Center;
}