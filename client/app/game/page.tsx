import Lobby from "@/components/game/lobby";

export default function Page() {
    const hasGameStarted: boolean = false;


    return hasGameStarted ? (
        <></>
        // <Game />
    ) : (
        <div className="flex flex-col items-center justify-center h-screen">
            <Lobby code={"123414"} owner={"Goat"} players={["Goat", "test"]}/>
        </div>
    );
}