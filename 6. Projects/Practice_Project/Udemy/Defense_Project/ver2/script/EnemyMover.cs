using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Enemy))]
public class EnemyMover : MonoBehaviour
{
    [SerializeField] [Range(0f, 5f)] float speed = 1f;

    List<Node> path = new List<Node>();

    Enemy enemy;
    GridManager gridManager;
    PathFinder pathFinder;

    void Awake()
    {
        enemy = GetComponent<Enemy>();
        gridManager = FindObjectOfType<GridManager>();
        pathFinder = FindObjectOfType<PathFinder>();
    }

    //life cycle -> awake => onenable => reset => start => fixedUpdate => update =>lateUpdate
    void OnEnable()
    {
        FindPath();
        ReturnToStart();
        StartCoroutine(FollowPath());
    }

    void FindPath()
    {
        path.Clear();
        path = pathFinder.GetnewPath();
        /*GameObject parent = GameObject.FindGameObjectWithTag("Path");
        foreach(Transform child in parent.transform)
        {
            Tile wayPoint = child.GetComponent<Tile>();

            if(wayPoint != null)
            {
                path.Add(wayPoint);
            }
        }*/
    }

    void ReturnToStart()
    {
        /*transform.position = path[0].transform.position;*/
        transform.position = gridManager.GetPositionFormCoordinates(pathFinder.StartCoordinates);
    }

    void FinishPath()
    {
        enemy.StealGold();
        gameObject.SetActive(false);
    }


    IEnumerator FollowPath()
    {
        /*foreach(Tile waypoint in path)*/
        for(int i=0;i<path.Count;i++)
        {
            Vector3 startPosition = transform.position;
            /*Vector3 endPosition = waypoint.transform.position;*/
            Vector3 endPosition = gridManager.GetPositionFormCoordinates(path[i].coordinates);
            float travelPercent = 0f;

            transform.LookAt(endPosition); //진행하고 있는 방향을 바라보도록 처리

            while(travelPercent < 1f) { //0~1로 셋업
                travelPercent += (Time.deltaTime * speed); //1프레임 움직임
                transform.position = Vector3.Lerp(startPosition, endPosition, travelPercent); // 선형 보간 -> 시작점, 끝점, 어느 지점에 위치할지.
                yield return new WaitForEndOfFrame(); //1프레임 끝날때, yield return
            }
        }

        FinishPath();
    }
}
