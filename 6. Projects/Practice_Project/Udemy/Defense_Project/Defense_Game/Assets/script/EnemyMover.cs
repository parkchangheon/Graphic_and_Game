using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Enemy))]
public class EnemyMover : MonoBehaviour
{
    [SerializeField] List<WayPoint> path = new List<WayPoint>();
    [SerializeField] [Range(0f, 5f)] float speed = 1f;
    Enemy enemy;

    void Start()
    {
        enemy = GetComponent<Enemy>();    
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

        GameObject parent = GameObject.FindGameObjectWithTag("Path");
        foreach(Transform child in parent.transform)
        {
            WayPoint wayPoint = child.GetComponent<WayPoint>();

            if(wayPoint != null)
            {
                path.Add(wayPoint);
            }
        }
    }

    void ReturnToStart()
    {
        transform.position = path[0].transform.position;
    }

    void FinishPath()
    {
        enemy.StealGold();
        gameObject.SetActive(false);
    }


    IEnumerator FollowPath()
    {
        foreach(WayPoint waypoint in path)
        {
            Vector3 startPosition = transform.position;
            Vector3 endPosition = waypoint.transform.position;
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
