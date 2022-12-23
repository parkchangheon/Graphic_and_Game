using System;
using System.Collections.Generic;
using System.Text;

namespace CSharp
{
    class TextMMO
    {
        enum ClassType
        {
            None =0,
            Knight =1,
            Archer=2,
            Mage=3
        }
        struct Player
        {
            public int hp;
            public int attack;
        }

        enum MonsterType
        {
            None,
            Goblin,
            Oak ,
            Skull
        }
        struct Monster
        {
            public int hp;
            public int attack;
        }




        static ClassType SelectClass()
        {
            ClassType choice = ClassType.None;

            Console.WriteLine("직업을 선택해주세요");
            Console.WriteLine("[1] 기사");
            Console.WriteLine("[2] 궁수");
            Console.WriteLine("[3] 법사");

            string result = Console.ReadLine();
            switch(result)
            {
                case "1":
                    choice = ClassType.Knight;
                    break;

                case "2":
                    choice = ClassType.Archer;
                    break;

                case "3":
                    choice = ClassType.Mage;
                    break;
            }

            return choice;
        }
        static void CreatePlayer(ClassType _classType, out Player _player)
        {
            _player.hp = 0;
            _player.attack = 0;

            switch(_classType)
            {
                case ClassType.Knight:
                    _player.hp = 100;
                    _player.attack = 10;
                    break;

                case ClassType.Archer:
                    _player.hp = 75;
                    _player.attack = 12;
                    break;

                case ClassType.Mage:
                    _player.hp = 50;
                    _player.attack = 15;
                    break;

                default:
                    _player.hp = 0;
                    _player.attack = 0;
                    break;
            }
        }
        static void CreateMonster(out Monster _monster)
        {
            
            Random random = new Random();
            int randMonsterNum = random.Next(1, 4);
            switch (randMonsterNum)
            {
                case 1:
                    Console.WriteLine("고블린이 생성되었습니다.");
                    _monster.hp = 10;
                    _monster.attack = 5;
                    break;

                case 2:
                    Console.WriteLine("오크가 생성되었습니다.");
                    _monster.hp = 20;
                    _monster.attack = 10; 
                    break;

                case 3:
                    Console.WriteLine("해골이 생성되었습니다.");
                    _monster.hp = 15;
                    _monster.attack = 7;
                    break;

                default:
                    _monster.hp = 0;
                    _monster.attack = 0;
                    break;
            }
        }


        static void Fight(ref Player player, ref Monster monster)
        {
            while(true)
            {
                monster.hp -= player.attack;
                if(monster.hp<=0)
                {
                    Console.WriteLine("승리했습니다.");
                    Console.WriteLine($"남은 체력 : {player.hp}");
                    break;
                }

                player.hp -= monster.hp;
                if(player.hp <= 0)
                {
                    Console.WriteLine("패배했습니다.");
                    break;
                }
            }
        }

        static void EnterField(ref Player _player)
        {
            while(true)
            {
                Console.WriteLine("필드에 접속했습니다.");

                //몬스터 생성
                Monster _monster;
                CreateMonster(out _monster);

                //전투모드로 돌입
                Console.WriteLine("[1] 전투모드 돌입");
                Console.WriteLine("[2] 일정확률로 마을로 도망");

                string input = Console.ReadLine();
                if (input == "1")
                {
                    Fight(ref _player, ref _monster);
                }

                else if (input == "2")
                {
                    // 33%
                    Random rand = new Random();
                    int randValue = rand.Next(0, 101);
                    if (randValue <= 33)
                    {
                        Console.WriteLine("도망치는데 성공했습니다.");
                        break;

                    }
                    else
                        Fight(ref _player, ref _monster);
                }
            }
            
        }


        static void EnterGame(ref Player player)
        {
            while(true)
            {
                Console.WriteLine("마을에 접속했습니다.");
                Console.WriteLine("[1] 필드로 간다");
                Console.WriteLine("[2] 로비로 돌아가기");

                string input = Console.ReadLine();
                if (input == "1")
                {
                    //EnterField;
                    EnterField(ref player);
                }
                else if (input == "2")
                {
                    break;
                }
            }
            
                    
                
        }

        static void Main(string[] args)
        {


            while(true)
            {
                ClassType _classType = TextMMO.SelectClass();
                if (_classType != ClassType.None)
                {
                    //캐릭터 생성 
                    Player player;
                    CreatePlayer(_classType, out player);

                    //필드로 가서 몬스터랑 싸운다.
                    EnterGame(ref player);
                }
            }
            




        }
    }

    
}
