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
	MoveAngle = 0.0;
	Speed = 0.0;
	Velocity.x = 0;
	Velocity.y = 0;
	Acceleration.x = 0;
	Acceleration.y = 0;
	Scene = nullptr;
	BoundAction = 0;
}

void Sprite::VectorProjection(double Speed)
{
	Velocity.x = Speed * cos(MoveAngle) + Acceleration.x;
	Velocity.y = Speed * sin(MoveAngle) + Acceleration.y;
	this->Speed = sqrt((Velocity.x * Velocity.x) + (Velocity.y * Velocity.y));
	MoveAngle = atan2(Velocity.y, Velocity.x);
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
		texture.w = 0.2*w;
		texture.h = 0.2*h;
		SetVertices();
		return Image;
	}
}

void Sprite::Draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, Image, NULL, &texture);
	SDL_RenderPresent(renderer);
}

void Sprite::Update(){}

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
	//std::cout << "P1 Normals: " << std::endl;
	//while (!P1Normals.empty())
	//{
	//	std::cout << "(" << P1Normals.top().x << ", " << P1Normals.top().y << ")" << std::endl;
	//	P1Normals.pop();
	//}
	//std::cout << "P2 Normals: " << std::endl;
	//while (!P2Normals.empty())
	//{
	//	std::cout << "(" << P2Normals.top().x << ", " << P2Normals.top().y << ")" << std::endl;
	//	P2Normals.pop();
	//}
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

void Sprite::SetVertices()
{
	Vec2D vert1{(double)texture.x, (double)texture.y};
	Vec2D vert2{(double)texture.x + (double)texture.w, (double)texture.y};
	Vec2D vert3{(double)texture.x, (double)texture.y + (double)texture.h};
	Vec2D vert4{(double)texture.x + (double)texture.w, (double)texture.y + (double)texture.h};
	vertices.push_back(vert1);
	vertices.push_back(vert3);
	vertices.push_back(vert4);
	vertices.push_back(vert2);
}

void Sprite::SetCollisionEnabled(bool Set)
{
	bCollisionEnabled = Set;
}

void Sprite::MoveSprite()
{
	Position.x += Velocity.x;
	Position.y += Velocity.y;
	for (Vec2D vert : vertices)
	{
		vert.x += Velocity.x;
		vert.y += Velocity.y;
	}
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
		Vec2D VectorOffset{ Position.x - OtherSprite->Position.x, Position.y - OtherSprite->Position.y };
		double ScalarOffset = VectorOffset.DotProduct(Normals.top());
		p1min += ScalarOffset;
		p1max += ScalarOffset;
		if (p1min - p2max > 0 || p2min - p1max > 0)
		{
			return false;
		}
		Normals.pop();
	}
	return true;
}