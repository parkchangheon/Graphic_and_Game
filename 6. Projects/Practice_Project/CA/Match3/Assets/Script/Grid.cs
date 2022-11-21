using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Grid : MonoBehaviour
{
    public enum PieceType
    {
        NORMAL,
        COUNT,
    }

    [System.Serializable]
    public struct PiecePrefab
    {
        public PieceType type;
        public GameObject prefab;
    }

    public PiecePrefab[] piecePrefabs;
    public GameObject backGroundPrefab;
    private Dictionary<PieceType, GameObject> piecePrefabDict;

    public int xDim;
    public int yDim;
    private GamePiece[,] pieces;
    void Start()
    {
        piecePrefabDict = new Dictionary<PieceType, GameObject>();
        for(int i=0 ; i < piecePrefabs.Length; i++)  //색별 과자
        {
            if (!piecePrefabDict.ContainsKey(piecePrefabs[i].type))
            {
                piecePrefabDict.Add(piecePrefabs[i].type, piecePrefabs[i].prefab);
            }
        }

        for(int x = 0; x<xDim; x++)     //타일 백그라운드
        {
            for(int y=0; y<yDim; y++)
            {
                GameObject background = (GameObject)Instantiate(backGroundPrefab, GetWorldPosition(x, y), Quaternion.identity);
                background.transform.parent = transform;
            
            }
        }

        pieces = new GamePiece[xDim, yDim];
        for (int x = 0; x < xDim; x++)      //시작시 생성
        {
            for (int y = 0; y < yDim; y++)
            {
                GameObject newPiece = (GameObject)Instantiate(piecePrefabDict[PieceType.NORMAL], Vector3.zero, Quaternion.identity);
                newPiece.name = "Piece(" + x + "," + y + ")";
                newPiece.transform.parent = transform;

                pieces[x, y] = newPiece.GetComponent<GamePiece>();
                pieces[x, y].Init(x, y, this, PieceType.NORMAL);

                if(pieces[x,y].IsMovable()) //색과자 움직이기 가능하다면
                {
                    pieces[x, y].MovableComponent.Move(x, y);
                }

                if(pieces[x,y].IsColored())
                {
                    pieces[x, y].ColorComponent.SetColor((ColorPiece.ColorType)Random.Range(0, pieces[x, y].ColorComponent.NumColors)); 
                }

            }
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public Vector2 GetWorldPosition(int x, int y)
    {
        return new Vector2(transform.position.x-xDim/2.0f+x, transform.position.y+yDim/2.0f-y);
    }

}
