using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Grid : MonoBehaviour
{
    public enum PieceType
    {
        EMPTY,
        NORMAL,
        OBSTACLE,
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
    public float fillTime;
    private GamePiece[,] pieces;

    private bool avoidance = false;

    //touch? click?
    private GamePiece pressedPiece;
    private GamePiece enteredPiece;

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

        pieces = new GamePiece[xDim, yDim]; //색과자
        for (int x = 0; x < xDim; x++)      //시작시 생성 
            for (int y = 0; y < yDim; y++)
                SpawnNewPiece(x, y, PieceType.EMPTY);

        Destroy(pieces[3, 2].gameObject);
        SpawnNewPiece(3, 2, PieceType.OBSTACLE);

        Destroy(pieces[1, 3].gameObject);
        SpawnNewPiece(1, 3, PieceType.OBSTACLE);

        StartCoroutine(Fill());
    }

    // Update is called once per frame
    void Update()
    {
            
    }

    public IEnumerator Fill()
    {
        while(FillStep())
        {
            avoidance = !avoidance;
            yield return new WaitForSeconds(fillTime);
        }
    }
    public bool FillStep()
    {
        bool movedPiece = false;
        for(int y = yDim-2; y>=0; y--)
        {
            for(int loopx =0; loopx<xDim; loopx++)
            {
                int x = loopx;
                if(avoidance)
                {
                    x = xDim - 1 - loopx;
                }

                GamePiece piece = pieces[x, y];
                if(piece.IsMovable())
                {
                    GamePiece pieceBelow = pieces[x, y + 1];
                    if(pieceBelow.Type == PieceType.EMPTY) //바로 아래가 비었는지 확인하는 로직
                    {
                        Destroy(pieceBelow.gameObject);
                        piece.MovableComponent.Move(x, y + 1, fillTime);
                        pieces[x, y + 1] = piece;
                        SpawnNewPiece(x, y, PieceType.EMPTY);
                        movedPiece = true;
                    }

                    else
                    {
                        for(int diag = -1; diag <=1; diag++) //양 사이드로 빠질 수 있게끔 하는 루프
                        {
                            if(diag != 0 ) //0이라면 바로 밑이고 아니니 옆으로 빠지는 로~직 하지만 위에서 이미 체크
                            {
                                int diagX = x + diag;
                                if(avoidance)
                                {
                                    diagX = x - diag;
                                }

                                if(diagX >= 0 && diagX <xDim)
                                {
                                    GamePiece diagonalPiece = pieces[diagX, y + 1];
                                    if(diagonalPiece.Type == PieceType.EMPTY)
                                    {
                                        bool hasPieceAbove = true;
                                        for( int aboveY = y; aboveY >=0; aboveY--)
                                        {
                                            GamePiece pieceAbove = pieces[diagX, aboveY];

                                            if(pieceAbove.IsMovable())
                                            {
                                                break;
                                            }
                                            else if(!pieceAbove.IsMovable() && pieceAbove.Type!= PieceType.EMPTY)
                                            {
                                                hasPieceAbove = false;
                                                break;
                                            }
                                        }

                                        if(!hasPieceAbove)
                                        {
                                            Destroy(diagonalPiece.gameObject);
                                            piece.MovableComponent.Move(diagX, y + 1, fillTime);
                                            pieces[diagX, y + 1] = piece;
                                            SpawnNewPiece(x, y, PieceType.EMPTY);
                                            movedPiece = true;
                                            break;
                                        }

                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        for(int x = 0; x<xDim; x++)
        {
            GamePiece pieceBelow = pieces[x, 0];
            if(pieceBelow.Type == PieceType.EMPTY)
            {
                Destroy(pieceBelow.gameObject);
                GameObject newPiece = (GameObject)Instantiate(piecePrefabDict[PieceType.NORMAL], GetWorldPosition(x,-1),Quaternion.identity);
                newPiece.transform.parent = transform;
                
                pieces[x, 0] = newPiece.GetComponent<GamePiece>();
                pieces[x, 0].Init(x, -1, this, PieceType.NORMAL);
                pieces[x, 0].MovableComponent.Move(x, 0, fillTime);
                pieces[x, 0].ColorComponent.SetColor((ColorPiece.ColorType)Random.Range(0,pieces[x,0].colorComponent.NumColors));
                movedPiece = true;
            }
        }

        return movedPiece;
    }


    public Vector2 GetWorldPosition(int x, int y)
    {
        return new Vector2(transform.position.x-xDim/2.0f+x, transform.position.y+yDim/2.0f-y);
    }


    public GamePiece SpawnNewPiece( int x, int y, PieceType type)
    {
        GameObject newPiece = (GameObject)Instantiate(piecePrefabDict[type], GetWorldPosition(x,y), Quaternion.identity);
        newPiece.transform.parent = transform;

        pieces[x, y] = newPiece.GetComponent<GamePiece>();
        pieces[x, y].Init(x, y, this, type);

        return pieces[x, y];

    }

    public bool IsAdjacent(GamePiece piece1, GamePiece piece2)
    {

        return (piece1.X == piece2.X && (int)Mathf.Abs(piece1.Y - piece2.Y)==1)
            || (piece1.Y == piece2.Y && (int)Mathf.Abs(piece1.X - piece2.X)==1);
    }

    public void SwapPieces(GamePiece piece1, GamePiece piece2)
    {
        if(piece1.IsMovable() && piece2.IsMovable())
        {
            pieces[piece1.X, piece1.Y] = piece2;
            pieces[piece2.X, piece2.Y] = piece1;

            if (GetMatch(piece1, piece2.X, piece2.Y) != null || GetMatch(piece2, piece1.X, piece1.Y) != null)
            {
                int piece1X = piece1.X;
                int piece1Y = piece1.Y;

                piece1.MovableComponent.Move(piece2.X, piece2.Y, fillTime);
                piece2.MovableComponent.Move(piece1X, piece1Y, fillTime);
            }
            else{
                pieces[piece1.X, piece1.Y] = piece1;
                pieces[piece2.X, piece2.Y] = piece2;
            }
        }
    }

    public void PreddPiece(GamePiece piece)
    {
        pressedPiece = piece;
    }

    public void EnterPiece(GamePiece piece)
    {
        enteredPiece = piece;
    }

    public void ReleasePiece()
    { 
        if(IsAdjacent(pressedPiece, enteredPiece))
        {
            SwapPieces(pressedPiece, enteredPiece);
        }
    }

    public List<GamePiece> GetMatch(GamePiece piece, int newX, int newY)
    {
        if (piece.IsColored())
        {
            ColorPiece.ColorType color = piece.ColorComponent.Color;
            List<GamePiece> horizontalPieces = new List<GamePiece>();
            List<GamePiece> VerticalPieces = new List<GamePiece>();
            List<GamePiece> matchingpieces = new List<GamePiece>();


            //horizontal 
            horizontalPieces.Add(piece);
            for (int dir = 0; dir <= 1; dir++)
            {
                for (int xOffset = 1; xOffset < xDim; xOffset++)
                {
                    int x;

                    if (dir == 0)
                        x = newX - xOffset;
                    else
                        x = newX + xOffset;
                    if (x < 0 || x >= xDim)
                    {
                        break;
                    }

                    //matching
                    if (pieces[x, newY].IsColored() && pieces[x, newY].ColorComponent.Color == color)
                        horizontalPieces.Add(pieces[x, newY]);

                    else
                        break;
                }
            }


            if (horizontalPieces.Count >= 3)
            {
                for (int i = 0; i < horizontalPieces.Count; i++)
                    matchingpieces.Add(horizontalPieces[i]);
            }

/*            if (horizontalPieces.Count >= 3)
            {
                for (int i = 0; i < horizontalPieces.Count; i++)
                {
                    for (int dir = 0; dir <= 1; dir++)
                    {
                        for (int yOffset = 1; yOffset < yDim; yOffset++)
                        {
                            int y;

                            if (dir == 0)
                                y = newY - yOffset;
                            
                            else
                                y = newY + yOffset;
                            
                            if (y < 0 || y >= yDim)
                                break;


                            if (pieces[horizontalPieces[i].X, y].ColorComponent.Color == color)
                                VerticalPieces.Add(pieces[horizontalPieces[i].X, y]);
                            else
                                break;
                            
                        }
                    }

                    if (VerticalPieces.Count < 2)
                        VerticalPieces.Clear();
                    
                    else
                    {
                        for (int j = 0; j < VerticalPieces.Count; j++)

                            matchingpieces.Add(VerticalPieces[j]);
                        
                        break;
                    }
                }
            }*/

            if (matchingpieces.Count >= 3){
                return matchingpieces;
            }
            


            //vertical
            VerticalPieces.Add(piece);

            for (int dir = 0; dir <= 1; dir++)
            {
                for (int yOffset = 1; yOffset < xDim; yOffset++)
                {
                    int y;

                    if (dir == 0)
                        y = newY - yOffset;
                    else
                        y = newY + yOffset;
                    if (y < 0 || y >= yDim)
                    {
                        break;
                    }

                    //matching
                    if (pieces[newX, y].IsColored() && pieces[newX, y].ColorComponent.Color == color)
                        VerticalPieces.Add(pieces[newX, y]);

                    else
                        break;
                }
            }

            if (VerticalPieces.Count >= 3)
            {
                for (int i = 0; i < VerticalPieces.Count; i++)
                    matchingpieces.Add(VerticalPieces[i]);
            }

            if (matchingpieces.Count >= 3)
                return matchingpieces;
            
        }
        return null;
    }

}
