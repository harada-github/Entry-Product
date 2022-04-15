//!============================================================
//!
//!  @file    : Model.cpp
//!  @brief   : モデルクラスのソースファイル
//!  @author  : 配布
//!  @details : モデルの実装
//!             アニメーションを使用しないオブジェクトはこのクラスを使用
//!
//!============================================================
#define _CRT_SECURE_NO_WARNINGS


//============================================================
//　インクルード
//============================================================
#include <stdio.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include "Main.h"
#include "Renderer.h"
#include "Model.h"


//============================================================
//　関数
//============================================================
//!-----------------------------------------------------------
//! @fn      : Draw()
//! @brief   : モデルの描画をする
//! @param   : なし
//! @return  : なし
//! @details : 描画設定をして描画を行う
//!-----------------------------------------------------------
void Model::Draw()
{
	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// インデックスバッファ設定
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	for( unsigned int i = 0; i < m_SubsetNum; i++ )
	{
		// マテリアル設定
		Renderer::SetMaterial( m_SubsetArray[i].Material.Material );

		// テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources( 0, 1, &m_SubsetArray[i].Material.Texture );

		// ポリゴン描画
		Renderer::GetDeviceContext()->DrawIndexed( m_SubsetArray[i].IndexNum, m_SubsetArray[i].StartIndex, 0 );
	}
}


//!-----------------------------------------------------------
//! @fn      : Load(const char *loadFileName)
//! @brief   : モデルのロードをする
//! @param   : loadFileName...ロードするファイルの名前
//! @return  : なし
//! @details : ファイルの読み込み
//!            頂点バッファとインデックスバッファを生成
//!            サブセット設定
//!-----------------------------------------------------------
void Model::Load( const char *loadFileName)
{
	MODEL model;
	LoadObj(loadFileName, &model );


	// 頂点バッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof( VERTEX_3D ) * model.VertexNum;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory( &sd, sizeof(sd) );
		sd.pSysMem = model.VertexArray;

		Renderer::GetDevice()->CreateBuffer( &bd, &sd, &m_VertexBuffer );
	}


	// インデックスバッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof( unsigned int ) * model.IndexNum;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory( &sd, sizeof(sd) );
		sd.pSysMem = model.IndexArray;

		Renderer::GetDevice()->CreateBuffer( &bd, &sd, &m_IndexBuffer );
	}


	// サブセット設定
	{
		m_SubsetArray = new SUBSET[ model.SubsetNum ];
		m_SubsetNum = model.SubsetNum;

		for( unsigned int i = 0; i < model.SubsetNum; i++ )
		{
			m_SubsetArray[i].StartIndex = model.SubsetArray[i].StartIndex;
			m_SubsetArray[i].IndexNum = model.SubsetArray[i].IndexNum;

			m_SubsetArray[i].Material.Material = model.SubsetArray[i].Material.Material;

			m_SubsetArray[i].Material.Texture = NULL;

			D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
				model.SubsetArray[i].Material.TextureName,
				NULL,
				NULL,
				&m_SubsetArray[i].Material.Texture,
				NULL);

			assert(m_SubsetArray[i].Material.Texture);

		}
	}

	delete[] model.VertexArray;
	delete[] model.IndexArray;
	delete[] model.SubsetArray;

}


//!-----------------------------------------------------------
//! @fn      : Unload()
//! @brief   : モデルのアンロードをする
//! @param   : なし
//! @return  : なし
//! @details : 頂点バッファとインデックスバッファの解放
//!            その他リリース処理を行う
//!-----------------------------------------------------------
void Model::Unload()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();

	for (unsigned int i = 0; i < m_SubsetNum; i++)
	{
		m_SubsetArray[i].Material.Texture->Release();
	}

	delete[] m_SubsetArray;

}


//!-----------------------------------------------------------
//! @fn         : LoadObj(const char *loadFileName, MODEL *loadModel)
//! @brief      : モデルの読み込み
//! @param arg1 : loadFileName....ロードするファイル名
//! @param arg2 : loadModel.......読み込んだデータから生成したものを格納
//! @return     : なし
//! @details    : ファイルの読み込み
//!               読み込んだファイルからモデルを生成
//!-----------------------------------------------------------
void Model::LoadObj(const char *loadFileName, MODEL *loadModel)
{
	// モデル読み込みに使用する変数
	char dir[MAX_PATH];
	strcpy (dir, loadFileName);
	PathRemoveFileSpec(dir);

	D3DXVECTOR3	*positionArray;
	D3DXVECTOR3	*normalArray;
	D3DXVECTOR2	*texcoordArray;

	unsigned int	positionNum = 0;
	unsigned int	normalNum = 0;
	unsigned int	texcoordNum = 0;
	unsigned int	vertexNum = 0;
	unsigned int	indexNum = 0;
	unsigned int	in = 0;
	unsigned int	subsetNum = 0;

	MODEL_MATERIAL	*materialArray = NULL;
	unsigned int	materialNum = 0;

	char str[256];
	char *s;
	char c;


	// ファイルの読み込み
	FILE *file;
	file = fopen( loadFileName, "rt" );
	assert(file);


	//要素数カウント
	while( true )
	{
		fscanf( file, "%s", str );

		if( feof( file ) != 0 )
			break;

		if( strcmp( str, "v" ) == 0 )
		{
			positionNum++;
		}
		else if( strcmp( str, "vn" ) == 0 )
		{
			normalNum++;
		}
		else if( strcmp( str, "vt" ) == 0 )
		{
			texcoordNum++;
		}
		else if( strcmp( str, "usemtl" ) == 0 )
		{
			subsetNum++;
		}
		else if( strcmp( str, "f" ) == 0 )
		{
			in = 0;

			do
			{
				fscanf( file, "%s", str );
				vertexNum++;
				in++;
				c = fgetc( file );
			}
			while( c != '\n' && c!= '\r' );

			//四角は三角に分割
			if( in == 4 )
				in = 6;

			indexNum += in;
		}
	}


	//メモリ確保
	positionArray = new D3DXVECTOR3[ positionNum ];
	normalArray   = new D3DXVECTOR3[ normalNum ];
	texcoordArray = new D3DXVECTOR2[ texcoordNum ];

	loadModel->VertexArray = new VERTEX_3D[ vertexNum ];
	loadModel->VertexNum   = vertexNum;

	loadModel->IndexArray  = new unsigned int[ indexNum ];
	loadModel->IndexNum    = indexNum;

	loadModel->SubsetArray = new SUBSET[ subsetNum ];
	loadModel->SubsetNum   = subsetNum;


	//要素読込
	D3DXVECTOR3 *position = positionArray;
	D3DXVECTOR3 *normal = normalArray;
	D3DXVECTOR2 *texcoord = texcoordArray;

	unsigned int vc = 0;
	unsigned int ic = 0;
	unsigned int sc = 0;

	fseek( file, 0, SEEK_SET );

	while( true )
	{
		fscanf( file, "%s", str );

		if( feof( file ) != 0 )
			break;

		if( strcmp( str, "mtllib" ) == 0 )
		{
			//マテリアルファイル
			fscanf( file, "%s", str );

			char path[256];
			strcpy( path, dir );
			strcat( path, "\\" );
			strcat( path, str );

			LoadMaterial( path, &materialArray, &materialNum );
		}
		else if( strcmp( str, "o" ) == 0 )
		{
			//オブジェクト名
			fscanf( file, "%s", str );
		}
		else if( strcmp( str, "v" ) == 0 )
		{
			//頂点座標
			fscanf( file, "%f", &position->x );
			fscanf( file, "%f", &position->y );
			fscanf( file, "%f", &position->z );
			position++;
		}
		else if( strcmp( str, "vn" ) == 0 )
		{
			//法線
			fscanf( file, "%f", &normal->x );
			fscanf( file, "%f", &normal->y );
			fscanf( file, "%f", &normal->z );
			normal++;
		}
		else if( strcmp( str, "vt" ) == 0 )
		{
			//テクスチャ座標
			fscanf( file, "%f", &texcoord->x );
			fscanf( file, "%f", &texcoord->y );
			texcoord->y = 1.0f - texcoord->y;
			texcoord++;
		}
		else if( strcmp( str, "usemtl" ) == 0 )
		{
			//マテリアル
			fscanf( file, "%s", str );

			if( sc != 0 )
				loadModel->SubsetArray[ sc - 1 ].IndexNum = ic - loadModel->SubsetArray[ sc - 1 ].StartIndex;

			loadModel->SubsetArray[ sc ].StartIndex = ic;


			for( unsigned int i = 0; i < materialNum; i++ )
			{
				if( strcmp( str, materialArray[i].Name ) == 0 )
				{
					loadModel->SubsetArray[ sc ].Material.Material = materialArray[i].Material;
					strcpy(loadModel->SubsetArray[ sc ].Material.TextureName, materialArray[i].TextureName );
					strcpy(loadModel->SubsetArray[ sc ].Material.Name, materialArray[i].Name );

					break;
				}
			}

			sc++;
			
		}
		else if( strcmp( str, "f" ) == 0 )
		{
			//面
			in = 0;

			do
			{
				fscanf( file, "%s", str );

				s = strtok( str, "/" );	
				loadModel->VertexArray[vc].Position = positionArray[ atoi( s ) - 1 ];
				if( s[ strlen( s ) + 1 ] != '/' )
				{
					//テクスチャ座標が存在しない場合もある
					s = strtok( NULL, "/" );
					loadModel->VertexArray[vc].TexCoord = texcoordArray[ atoi( s ) - 1 ];
				}
				s = strtok( NULL, "/" );	
				loadModel->VertexArray[vc].Normal = normalArray[ atoi( s ) - 1 ];

				loadModel->VertexArray[vc].Diffuse = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 1.0f );

				loadModel->IndexArray[ic] = vc;
				ic++;
				vc++;

				in++;
				c = fgetc( file );
			}
			while( c != '\n' && c != '\r' );

			//四角は三角に分割
			if( in == 4 )
			{
				loadModel->IndexArray[ic] = vc - 4;
				ic++;
				loadModel->IndexArray[ic] = vc - 2;
				ic++;
			}
		}
	}

	if( sc != 0 )
		loadModel->SubsetArray[ sc - 1 ].IndexNum = ic - loadModel->SubsetArray[ sc - 1 ].StartIndex;

	// ファイルを閉じる
	fclose( file );

	// 使用した変数の解放
	delete[] positionArray;
	delete[] normalArray;
	delete[] texcoordArray;
	delete[] materialArray;
}


//!-----------------------------------------------------------
//! @fn         : LoadMaterial(const char *loadFileName, MODEL_MATERIAL **loadMaterialArray, unsigned int *loadMaterialNum)
//! @brief      : マテリアル読み込み
//! @param arg1 : loadFileName............ロードするファイル名
//! @param arg2 : loadMaterialArray.......読み込んだデータからマテリアルを配置
//! @param arg3 : loadMaterialNum.........読み込んだデータからマテリアル数を格納
//! @return     : なし
//! @details    : ファイルの読み込み
//!               読み込んだファイルからマテリアルを生成
//!-----------------------------------------------------------
void Model::LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned int *MaterialNum )
{
	// マテリアル読み込みの使用する変数
	char dir[MAX_PATH];
	strcpy(dir, FileName);
	PathRemoveFileSpec(dir);

	char str[256];

	MODEL_MATERIAL *materialArray;
	unsigned int materialNum = 0;


	// ファイルの読み込み
	FILE *file;
	file = fopen( FileName, "rt" );
	assert(file);


	//要素数カウント
	while( true )
	{
		fscanf( file, "%s", str );

		if( feof( file ) != 0 )
			break;

		if( strcmp( str, "newmtl" ) == 0 )
		{
			materialNum++;
		}
	}


	//メモリ確保
	materialArray = new MODEL_MATERIAL[ materialNum ];


	//要素読込
	int mc = -1;

	fseek( file, 0, SEEK_SET );

	while( true )
	{
		fscanf( file, "%s", str );

		if( feof( file ) != 0 )
			break;


		if( strcmp( str, "newmtl" ) == 0 )
		{
			//マテリアル名
			mc++;
			fscanf( file, "%s", materialArray[ mc ].Name );
			strcpy( materialArray[ mc ].TextureName, "" );

			materialArray[mc].Material.Emission.r = 0.0f;
			materialArray[mc].Material.Emission.g = 0.0f;
			materialArray[mc].Material.Emission.b = 0.0f;
			materialArray[mc].Material.Emission.a = 0.0f;
		}
		else if( strcmp( str, "Ka" ) == 0 )
		{
			//アンビエント
			fscanf( file, "%f", &materialArray[ mc ].Material.Ambient.r );
			fscanf( file, "%f", &materialArray[ mc ].Material.Ambient.g );
			fscanf( file, "%f", &materialArray[ mc ].Material.Ambient.b );
			materialArray[ mc ].Material.Ambient.a = 1.0f;
		}
		else if( strcmp( str, "Kd" ) == 0 )
		{
			//ディフューズ
			fscanf( file, "%f", &materialArray[ mc ].Material.Diffuse.r );
			fscanf( file, "%f", &materialArray[ mc ].Material.Diffuse.g );
			fscanf( file, "%f", &materialArray[ mc ].Material.Diffuse.b );
			materialArray[ mc ].Material.Diffuse.a = 1.0f;
		}
		else if( strcmp( str, "Ks" ) == 0 )
		{
			//スペキュラ
			fscanf( file, "%f", &materialArray[ mc ].Material.Specular.r );
			fscanf( file, "%f", &materialArray[ mc ].Material.Specular.g );
			fscanf( file, "%f", &materialArray[ mc ].Material.Specular.b );
			materialArray[ mc ].Material.Specular.a = 1.0f;
		}
		else if( strcmp( str, "Ns" ) == 0 )
		{
			//スペキュラ強度
			fscanf( file, "%f", &materialArray[ mc ].Material.Shininess );
		}
		else if( strcmp( str, "d" ) == 0 )
		{
			//アルファ
			fscanf( file, "%f", &materialArray[ mc ].Material.Diffuse.a );
		}
		else if( strcmp( str, "map_Kd" ) == 0 )
		{
			//テクスチャ
			fscanf( file, "%s", str );

			char path[256];
			strcpy( path, dir );
			strcat( path, "\\" );
			strcat( path, str );

			strcat( materialArray[ mc ].TextureName, path );
		}
	}

	fclose(file);

	*MaterialArray = materialArray;
	*MaterialNum = materialNum;
}

